#include "Poly.h"
#include <iostream>
//#include <string>

Poly::Poly()
{
	// TODO
	head = new PolyNode(-1, 0, NULL);
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
	// TODO

	head = new PolyNode(-1,0,NULL);
	PolyNode* ptr = head;
	for(int i=0; i<coeff.size(); i++){
		PolyNode* newNode = new PolyNode(deg[i], coeff[i], NULL);
		ptr->next = newNode;
		ptr = ptr->next;
	}
}

Poly::~Poly()
{
	// TODO
	PolyNode* ptr = head;
	PolyNode* temp = head;
	while (ptr->next != NULL) {
		ptr = ptr->next;
		delete temp;
		temp = ptr;
	}
	delete ptr;
}

void Poly::addMono(int i, double c)
{
	// TODO
	if(c==0){return;}
	PolyNode* ptr = head;
	PolyNode* temp;
	while(ptr->next!=NULL){
		if(i == ptr->next->deg){
			ptr->next->coeff += c;
			if(ptr->next->coeff == 0){
				temp = ptr->next;
				ptr->next = ptr->next->next;
				delete temp;
			}
			return;
		}
		else if(i > ptr->next->deg){
			PolyNode* newNode = new PolyNode(i,c, ptr->next);
			ptr->next = newNode;
			return;
		}
		ptr = ptr->next;
	}
	ptr->next = new PolyNode(i,c,NULL);
	return;
}

void Poly::addPoly(const Poly& p)
{

	// TODO
	PolyNode* ptr = p.head;
	while(ptr->next){
		addMono(ptr->next->deg, ptr->next->coeff);
		ptr = ptr->next;
	}
}

void Poly::multiplyMono(int i, double c)
{
	// TODO

	PolyNode* ptr = head;

	// if coeff is 0 delete all nodes except head and point head to NULL
	if(c == 0 && getDegree() != -1){
		ptr = ptr->next;
		PolyNode* temp = ptr;
		while(ptr->next!=NULL){
			ptr = ptr->next;
			delete temp;
			temp = ptr;
		}
		delete ptr;
		head->next = NULL;
		return;
	}
	while(ptr->next != NULL){
		ptr->next->deg += i;
		ptr->next->coeff *= c;
		ptr = ptr->next;
	}
}

void Poly::multiplyPoly(const Poly& p)
{
	// TODO
	//check if this polynomial is 0
	if(getDegree() == -1){return;}
	PolyNode* ptr = p.head;

	Poly* multiplier = new Poly();
	duplicate(*multiplier);
	Poly* temp = new Poly();

	Poly* product = new Poly();

	/* FIX THIS AND UR DONE*/
	while (ptr->next != NULL){
		multiplier->duplicate(*temp);
		temp->multiplyMono(ptr->next->deg, ptr->next->coeff);
		product->addPoly(*temp);
		ptr = ptr->next;
	}
	product->duplicate(*this);
}

void Poly::duplicate(Poly& outputPoly)
{
	// TODO
	PolyNode* ptr1 = head;
	PolyNode* ptr2 = outputPoly.head;
	PolyNode* temp;
	PolyNode* storage;
	while(ptr1->next != NULL){
		if(ptr2->next != NULL){
			ptr2->next->coeff = ptr1->next->coeff;
			ptr2->next->deg = ptr1->next->deg;
		}
		else{ptr2->next = new PolyNode(ptr1->next->deg, ptr1->next->coeff, NULL);}

		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}

	// if input polynomial is larger than this object polynomial then delete extra nodes
	if(ptr2->next!=NULL){
		storage = ptr2;
		while(ptr2->next != NULL){
			temp = ptr2->next;
			ptr2 = ptr2->next;
			delete temp;
		}
		delete ptr2;
		storage->next = NULL;
		}
}

int Poly::getDegree()
{
	// TODO
	if(head->next == NULL){return head->deg;}
	return head->next->deg;//change this after completing this function
}

int Poly::getTermsNo()
{
	// TODO
	PolyNode* ptr = head->next;
	int terms = 0;
	while(ptr!=NULL){
		terms++;
		ptr = ptr->next;
	}
	return terms;//change this after completing this function
}

double Poly::evaluate(double x)
{
	// TODO
	double sum = 0;
	double term;
	PolyNode* ptr = head->next;
	while(ptr!=NULL){
		term = 1;
		for(int i=0;i<ptr->deg;i++){
			term *= x;
		}
		term *= ptr->coeff;
		sum += term;
		ptr = ptr->next;
	}
	return sum;//change this after completing this function
}

std::string Poly::toString()
{
	// TODO
	std::string output = "";
	PolyNode* ptr = head->next;
	output += "degree=" + std::to_string(getDegree()) + ";";
	if(ptr==NULL){output += " a(-1)=0;";}
	for(int i=0;i<getTermsNo();i++, ptr = ptr->next){
		output += " a(" + std::to_string(ptr->deg) + ")=" + std::to_string(ptr->coeff) + ";";
	}
	return output;//change this after completing this function
}
