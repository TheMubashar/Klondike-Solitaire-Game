// game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
using namespace std;

 //1 C B 13
 //14 S B 26
 //27 H R 39
 //40 D R 52


void CardValueDisplay(int &value) {
	if (value == 11 || value == 24 || value == 37 || value == 50) {
		cout << "J ";
	}
	else if (value == 12 || value == 25 || value == 38 || value == 51) {
		cout << "Q ";
	}
	else if (value == 13 || value == 26 || value == 39 || value == 52) {
		cout << "K ";
	}
	else if (value == 1 || value == 14 || value == 27 || value == 40) {
		cout << "A ";
	}
	else {
		if (value<14){
			cout << value << " ";
		}
		else if (value<27) {
			cout << value - 13 << " ";
		}
		else if (value<40) {
			cout << value - 26<< " ";
		}
		else if (value<53) {
			cout << value - 39 << " ";
		}
	}
}

class Card{
public:
	Card() {
		card = 1 + rand() % (52 - 1 + 1);
	}
	Card(int d) {
		card = d;
	}
	void SetCard(int d) {
		card = d;
	}
	int GetCard() {
		return card;
	}
	void display() {
		if (card >= 1 && card <14) {
			cout << "B ";
			cout <<"C ";
			CardValueDisplay(card);
		}
		else if (card >= 14 && card <27) {
			cout << "B ";
			cout << "S ";
			CardValueDisplay(card);
		}
		else if (card >= 27 && card <40) {
			cout << "R ";
			cout << "H ";
			CardValueDisplay(card);
		}
		else{
			cout << "R ";
			cout << "D ";
			CardValueDisplay(card);
		}
	}
	~Card() {

	}
private:
	int card;
};

class Node {
public:
	Node() {
		next = NULL;
	}
	Node(int d) : data(d) {
		next = NULL;
	}
	int getData() {
		return data.GetCard();
	}
	Node* getNext() {
		return next;
	}
	void setNext(Node * n) {
		next = n;
	}
	void setData(int d) {
		data.SetCard(d);
	}
	void display() {
		data.display();
	}
private:
	Card data;
	Node * next;

};

class Stack {
public:
	int DisplayNumberOfCards;
	Stack() {
		size = 0; 
		top = NULL;
		DisplayNumberOfCards = 1;
	}
	bool TableauPush(Node *&n,int CardSelection){
		if (top == NULL && (n->getData() == 13 || n->getData() == 26 || n->getData() == 39 || n->getData() == 52)) {
			top = n;
			for (int i = 1; i <= CardSelection; i++) {
				size++;
			}
			return true;
		}
		else {
			if (top->getData()>27){
				if (top->getData() > 39) {
					if ((n->getData() == top->getData() - 27) || (n->getData() == top->getData() - 40)) {
						n->setNext(top);
						top = n;
						for (int i = 1; i <= CardSelection; i++){
							size++;
						}
						return true;
					}
					else {
						cout << "You are placing card at wrong position" << endl;
						return false;
					}
				}
				else {
					if ((n->getData() == top->getData() - 27) || (n->getData() == top->getData() - 14)) {
						n->setNext(top);
						top = n;
						for (int i = 1; i <= CardSelection; i++) {
							size++;
						}
						return true;
					}
					else {
						cout << "You are placing card at wrong position" << endl;
						return false;
					}
				}
			}
			else {
				if (top->getData()>14){
					if ((n->getData() == top->getData() + 25) || (n->getData() == top->getData() + 12)) {
						n->setNext(top);
						top = n;
						for (int i = 1; i <= CardSelection; i++) {
							size++;
						}
						return true;
					}
					else {
						cout << "You are placing card at wrong position" << endl;
						return false;
					}
				}
				else {
					if ((n->getData() == top->getData() +25) || (n->getData() == top->getData() + 38)) {
						n->setNext(top);
						top = n;
						for (int i = 1; i <= CardSelection; i++) {
							size++;
						}
						return true;
					}
					else {
						cout << "You are placing card at wrong position" << endl;
						return false;
					}
				}
			}
		}
	}
	bool FoundationPush(Node *&n) {
		if (top == NULL && (n->getData() == 1 || n->getData() == 14 || n->getData() == 27 || n->getData() == 40)) {
			top = n;
			size++;
			return true;
		}
		else if(size!=0){
			if (n->getData() == (top->getData() + 1)) {
				n->setNext(top);
				top = n;
				size++;
				return true;
			}
			else {
				cout << "You are placing card at wrong position" << endl;
				return false;
			}
		}
		else {
			cout << "You are placing card at wrong position" << endl;
			return false;
		}
	}
	void push(int d) {
		Node * n = new Node(d);
		if (top == NULL) {
			top = n;
		}
		else {
			n->setNext(top);
			top = n;
		}		
		size++;
	}
	void pop(Stack &S,int NumberOfCards) {
		for (int i = 0; i < NumberOfCards; i++){
			if (S.top == NULL) {
				S.top = top;
				top = top->getNext();
				S.top->setNext(NULL);	
			}
			else {
				Node *temp = top;
				top = top->getNext();
				temp->setNext(S.top);
				S.top = temp;
			}	
		}
	}
	void Shuffle() {
		Node *Prev = top;
		Node *Next = top->getNext();
		for (int k = 0; k < 2; k++){
			for (int j = 1; j < 53; j++) {
				for (int i = 1; i < (1 + rand() % (52 - 1 + 1)); i++) {
					Next = Next->getNext();
				}
				int temp = Next->getData();
				Next->setData(Prev->getData());
				Prev->setData(temp);
				Prev = Prev->getNext();
				Next = top;
			}
			Prev = top;
			Next = top->getNext();
		}
	}
	void MoveCardFT(Stack &S, char insertinto, int &NRowDisplay,int CardSelection) {
		if (top != NULL) {
			Node * temp = top;
			Node * ForBackMovement = top;
			bool PushStack = S.top != NULL;
			if (CardSelection > 1) {
				for (int i = 1; i < CardSelection; i++){
					temp=temp->getNext();
				}
				if (temp->getNext()!=NULL){
					top = temp->getNext();
				}
				else {
					top = NULL;
				}
				temp->setNext(NULL);
				if (!S.TableauPush(temp,CardSelection)) {
					temp->setNext(top);
					top = ForBackMovement;
				}
				else {
					S.top = ForBackMovement;
					if (PushStack){
						for (int i = 0; i <CardSelection; i++) {
							S.DisplayNumberOfCards++;
						}
					}
					else {
						for (int i = 1; i < CardSelection; i++) {
							S.DisplayNumberOfCards++;
						}
					}
					if (DisplayNumberOfCards > 1) {
						for (int i = 1; i <CardSelection; i++){
							DisplayNumberOfCards--;
						}
					}
				}
			}
			else {
				top = top->getNext();
				temp->setNext(NULL);
				if (insertinto == 'F') {
					if (!S.FoundationPush(temp)) {
						temp->setNext(top);
						top = temp;
					}
					if (DisplayNumberOfCards>1) {
						DisplayNumberOfCards--;
					}
				}
				else {
					if (!S.TableauPush(temp,1)) {
						temp->setNext(top);
						top = temp;
					}
					else {
						if (PushStack) {
							S.DisplayNumberOfCards++;
						}
						if (DisplayNumberOfCards>1){
							DisplayNumberOfCards--;
						}
					}
				}
			}	
		}
		else {
			cout << "No card !!!" << endl;
		}
	}
	void MoveCardW(Stack &S, char insertinto,int &WastePileNumber, Node *&WastePileTop,int &NRowDisplay) {
		if (top != NULL) {
			Node * temp = top;
			top = top->getNext();
			bool PushStack = S.top != NULL;
			if (WastePileNumber==1){
				temp->setNext(NULL);
				if (insertinto == 'F') {
					if (!S.FoundationPush(temp)) {
						temp->setNext(top);
						top = temp;
					}
				}
				else {
					if (!S.TableauPush(temp,1)) {
						temp->setNext(top);
						top = temp;
					}
					else {
						if (PushStack) {
							S.DisplayNumberOfCards++;
						}
						top = top->getNext();
					}
				}
			}
			else{
				Node *Prev = WastePileTop;
				while (Prev->getNext()!=temp){
					Prev = Prev->getNext();
				}
				Prev->setNext(temp->getNext());
				temp->setNext(NULL);
				if (insertinto == 'F') {
					if (!S.FoundationPush(temp)) {
						temp->setNext(Prev->getNext());
						Prev->setNext(temp);
						top = temp;
					}
				}
				else {
					if (!S.TableauPush(temp,1)) {
						temp->setNext(Prev->getNext());
						Prev->setNext(temp);
						top = temp;
					}
					else{
						if (PushStack) {
							for (int i = 0; i <1; i++) {
								S.DisplayNumberOfCards++;
							}
						}
					}
				}
			}
		}
		else {
			cout << "No card !!!" << endl;
		}
	}
 	void display(int Ntimes) {
		if (top==NULL){
			cout << "0" ;
		}
		else{
			Node *temp = top;
			for (int i = 1; i <Ntimes; i++){
				temp = temp->getNext();
			}
			temp->display();
		}
	}
	void WastePileDisplay(int &WastePileNumber, Node *&WastePileTop, int &WastePileRotation) {
		int j;
		Node *temp = top;
		cout << "|";
		if (top == NULL) {
			cout << "|   0  |  0  |   0   |";
			WastePileNumber = 1;
			WastePileRotation++;
			top = WastePileTop;
		}
		else{
			for (j = 1; j < 3; j++) {
				if (temp->getNext() != NULL) {
					temp = temp->getNext();
				}
				else {
					break;
				}
			}
			if (j != 3) {
				cout << "   0  ";
			}
			else {
				temp->display();
			}
			cout << "|";
			temp = top;
			for (j = 1; j < 2; j++) {
				if (temp->getNext() != NULL) {
					temp = temp->getNext();
				}
				else {
					break;
				}
			}
			if (j != 2) {
				cout << "   0  ";
			}
			else {
				temp->display();
			}
			cout << "|";
			temp = top;
			if (temp != NULL) {
				temp = top;
				temp->display();
				cout << "|";
			}
			else {
				cout << "   0  ";
			}
		}
	}
	void ShowNextWastePile(int &WastePileNumber,Node *&WastePileTop,int &WastePileRotation) {
		if (WastePileNumber == 0) {
			top = WastePileTop;
			WastePileRotation++;
		}
		else if (WastePileNumber == 1) {
			WastePileTop = top;
			top = top->getNext()->getNext()->getNext();
		} 
		else{
			if (top->getNext()==NULL )  {
				WastePileNumber = 0;
				WastePileRotation++;
				top = WastePileTop;
			}
			else if (top->getNext()->getNext() == NULL) {
				WastePileNumber = 0;
				WastePileRotation++;
				top = WastePileTop;
			}
			else if(top->getNext()->getNext()->getNext() == NULL) {
				WastePileNumber = 0;
				WastePileRotation++;
				top = WastePileTop;
			}
			else {
				top = top->getNext()->getNext()->getNext();
			}
		}
	}
	Node * GetTop() {
		return top;
	}
private:	
	Node * top;
	int size;
};

int GameResult(Stack &Foundation1, Stack &Foundation2, Stack &Foundation3, Stack &Foundation4, int &WastePileRotation) {
	if (Foundation1.GetTop()!=NULL){
		int TempData = Foundation1.GetTop()->getData();
		if (TempData == 13 || TempData == 26 || TempData == 39 || TempData == 52) {
			if (Foundation2.GetTop() != NULL) {
				TempData = Foundation2.GetTop()->getData();
				if (TempData == 13 || TempData == 26 || TempData == 39 || TempData == 52) {
					if (Foundation3.GetTop() != NULL) {
						TempData = Foundation3.GetTop()->getData();
						if (TempData == 13 || TempData == 26 || TempData == 39 || TempData == 52) {
							if (Foundation4.GetTop() != NULL) {
								TempData = Foundation4.GetTop()->getData();
								if (TempData == 13 || TempData == 26 || TempData == 39 || TempData == 52) {
									return 1;
								}
							}
						}
					}
				}
			}
		}
	}
	if (WastePileRotation>=10) {
		return -1;
	}
	else {
		return 0;
	}
}
void GameDisplay(Stack &S1, Stack &S2, Stack &S3, Stack &S4, Stack &S5, Stack &S6, Stack &S7, Stack &Foundation1, Stack &Foundation2, Stack &Foundation3, Stack &Foundation4, Stack &WastePile, int &WastePileNumber, int &NRowDisplay, Node *&WastePileTop, int &WastePileRotation) {
	cout << " ====================" << endl;
	if (WastePileNumber == 0) {
		cout << "|   0  |  0  |   0   |";
	}
	else {
		WastePile.WastePileDisplay(WastePileNumber, WastePileTop, WastePileRotation);
	}
	cout << endl;
	cout << " ====================	";
	Foundation1.display(1); cout << "	"; Foundation2.display(1); cout << "	"; Foundation3.display(1); cout << "	"; Foundation4.display(1); cout << endl;
	cout << "======================================================" << endl;
	for (int i = 0; i < NRowDisplay; i++) {
		if (S1.DisplayNumberOfCards> i) {
			S1.display(S1.DisplayNumberOfCards-i);
		}
		else {
			cout << "      ";
		}
		cout << "	";
		if (S2.DisplayNumberOfCards> i) {
			S2.display(S2.DisplayNumberOfCards - i);
		}
		else {
			cout << "      ";
		}
		cout << "	";
		if (S3.DisplayNumberOfCards> i) {
			S3.display(S3.DisplayNumberOfCards - i);
		}
		else {
			cout << "      ";
		}
		cout << "	";
		if (S4.DisplayNumberOfCards> i) {
			S4.display(S4.DisplayNumberOfCards - i);
		}
		else {
			cout << "      ";
		}
		cout << "	";
		if (S5.DisplayNumberOfCards> i) {
			S5.display(S5.DisplayNumberOfCards - i);
		}
		else {
			cout << "      ";
		}
		cout << "	";
		if (S6.DisplayNumberOfCards> i) {
			S6.display(S6.DisplayNumberOfCards - i);
		}
		else {
			cout << "      ";
		}
		cout << "	";
		if (S7.DisplayNumberOfCards> i) {
			S7.display(S7.DisplayNumberOfCards - i);
		}
		else {
			cout << "      ";
		}
		cout << endl;
	}
}
void SelectCard(Stack &S,int &Selection) {
	while (true) {
		cout << "Enter the card position you want to select" << endl;
		cin >> Selection;
		if (Selection < (S.DisplayNumberOfCards + 1) && Selection > 0) {
			break;
		}
		else {
			cout << "You have made wrong selection. Select once again" << endl;
		}
	}
}
Stack& SelectTableau(int &To, Stack &S1, Stack &S2, Stack &S3, Stack &S4, Stack &S5, Stack &S6, Stack &S7) {
	if (To == 1) {
		return S1;
	}
	else if (To == 2) {
		return S2;
	}
	else if (To == 3) {
		return S3;
	}
	else if (To == 4) {
		return S4;
	}
	else if (To == 5) {
		return S5;
	}
	else if (To == 6) {
		return S6;
	}
	else {
		return S7;
	}
}
Stack& SelectFoundation(int &To, Stack &Foundation1, Stack &Foundation2, Stack &Foundation3, Stack &Foundation4) {
	if (To == 1) {
		return Foundation1;
	}
	else if (To == 2) {
		return Foundation2;
	}
	else if (To == 3) {
		return Foundation3;
	}
	else {
		return Foundation4;
	}
}
int main()
{
	int count = 2,from=0,to=0,WastePileNumber=0,WastePileRotation=0,NRowDisplay=1,Result;
	srand(time(NULL));
	Stack Compare, Foundation1,Foundation2,Foundation3,Foundation4, S1, S2, S3, S4, S5, S6, S7, WastePile;
	Node *WastePileTop;
	for (int i = 1; i < 53; i++){
		Compare.push(i);
	}
	Compare.Shuffle();
	Compare.pop(S1, 1);
	Compare.pop(S2, 2);
	Compare.pop(S3, 3);
	Compare.pop(S4, 4);
	Compare.pop(S5, 5);
	Compare.pop(S6, 6);
	Compare.pop(S7, 7);
	Compare.pop(WastePile, 24);
	GameDisplay(S1,S2,S3,S4,S5,S6,S7,Foundation1,Foundation2,Foundation3,Foundation4, WastePile, WastePileNumber, NRowDisplay, WastePileTop, WastePileRotation);
	cout << endl << endl;
	while (WastePileRotation<=15){
		cout << "Select from the following" << endl;
		cout << "Press 1 to move the card from Foundation" << endl;
		cout << "Press 2 to move the card from WastePile or to check the next 3 card" << endl;
		cout << "Press 3 to move the card from Tableau" << endl << "Selection: ";
		cin >> from;
		if (from == 1) {
			while (true) {
				for (int i = 1; i <= 4; i++) {
					cout << "Press " << i << " to move the card from Foundation " << i << endl;
				}
				cout << "Foundation Number: ";
				cin >> from;
				if (from < 5 && from > 0) {
					break;
				}
				else {
					cout << " Incorrect selection! \n Select once again " << endl;
				}
			}
			while (true) {
				for (int i = 1; i <= 7; i++) {
					cout << "Press " << i << " to move the card to Tableau " << i << endl;
				}
				cout << "Tableau Number: ";
				cin >> to;
				if (to < 8 && to > 0) {
					break;
				}
				else {
					cout << " Incorrect selection! \n Select once again " << endl;
				}
			}
			if (from == 1) {
				Foundation1.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T',NRowDisplay, 1);
			}
			else if (from == 2) {
				Foundation2.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
			}
			else if (from == 3) {
				Foundation3.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
			}
			else if (from == 4) {
				Foundation4.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
			}
		}
		else if (from == 2) {
			while (true){
				cout << "Press 1 to show the pile" << endl;
				cout << "Press 2 to move the card from WastePile" << endl;
				cout << "Selection: ";
				cin >> from;
				if (from < 3 && from > 0) {
					break;
				}
				else {
					cout << " Incorrect selection! \n Select once again " << endl;
				}
			}
			if (from==1){
				if (WastePileRotation==0) {
					if (WastePileNumber == 0) {
						WastePileNumber++;
					}
					WastePileRotation++;
				}
				else {
					if (WastePileNumber == 0) {
						WastePile.ShowNextWastePile(WastePileNumber, WastePileTop, WastePileRotation);
						WastePileNumber++;
					}
					else {
						if (WastePileNumber < 8) {
							WastePile.ShowNextWastePile(WastePileNumber, WastePileTop, WastePileRotation);
							WastePileNumber++;
						}
						else {
							WastePileNumber = 0;
						}
					}
				}
			}
			else {
				while (true) {
					cout << "Press 1 to move the card to Foundation" << endl;
					cout << "Press 2 to move the card to Tableau" << endl;
					cout << "Selection: ";
					cin >> from;
					if (from < 3 && from > 0) {
						break;
					}
					else {
						cout << " Incorrect selection! \n Select once again " << endl;
					}
				}
				if (from == 1) {
					while (true) {
						for (int i = 1; i <= 4; i++) {
							cout << "Press " << i << " to move the card to Foundation " << i << endl;
						}
						cout << "Foundation Number: ";
						cin >> to;
						if (to < 5 && to > 0) {
							break;
						}
						else {
							cout << " Incorrect selection! \n Select once again " << endl;
						}
					}
					if (WastePileNumber==0){
						cout << "First open the pile" << endl;
					}
					else  {
						WastePile.MoveCardW(SelectFoundation(to, Foundation1, Foundation2, Foundation3, Foundation4), 'F',WastePileNumber, WastePileTop, NRowDisplay);
					}
					
				}
				else {
					while (true) {
						for (int i = 1; i <= 7; i++) {
							cout << "Press " << i << " to move the card to Tableau " << i << endl;
						}
						cout << "Tableau Number: ";
						cin >> to;
						if (from < 8 && from > 0) {
							break;
						}
						else {
							cout << " Incorrect selection! \n Select once again " << endl;
						}
					}

					if (WastePileNumber == 0) {
						cout << "First open the pile" << endl;
					}
					else {
						WastePile.MoveCardW(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', WastePileNumber, WastePileTop, NRowDisplay);
					}
				}
			}
			
		}
		else {
			int tableaufrom;
			while (true) {
				for (int i = 1; i <= 7; i++) {
					cout << "Press " << i << " to move the card from Tableau " << i << endl;
				}
				cout << "Tableau Number: ";
				cin >> tableaufrom;
				if (tableaufrom < 8 && tableaufrom > 0) {
					break;
				}
				else {
					cout << " Incorrect selection! \n Select once again " << endl;
				}
			}
			while (true) {
				cout << "Press 1 to move the card to Foundation" << endl;
				cout << "Press 2 to move the card to Tableau" << endl;
				cout << "Selection: ";
				cin >> from;
				if (from < 3 && from > 0) {
					break;
				}
				else {
					cout << " Incorrect selection! \n Select once again " << endl;
				}
			}
			if (from == 1) {
				while (true) {
					for (int i = 1; i <= 4; i++) {
						cout << "Press " << i << " to move the card to Foundation " << i << endl;
					}
					cout << "Foundation Number: ";
					cin >> to;
					if (to < 5 && to > 0) {
						break;
					}
					else {
						cout << " Incorrect selection! \n Select once again " << endl;
					}
				}
				if (tableaufrom == 1) {
					S1.MoveCardFT(SelectFoundation(to, Foundation1, Foundation2, Foundation3, Foundation4), 'F', NRowDisplay, 1);
				}
				else if (tableaufrom == 2) {
					S2.MoveCardFT(SelectFoundation(to, Foundation1, Foundation2, Foundation3, Foundation4), 'F', NRowDisplay, 1);
				}
				else if (tableaufrom == 3) {
					S3.MoveCardFT(SelectFoundation(to, Foundation1, Foundation2, Foundation3, Foundation4), 'F', NRowDisplay, 1);
				}
				else if (tableaufrom == 4) {
					S4.MoveCardFT(SelectFoundation(to, Foundation1, Foundation2, Foundation3, Foundation4), 'F', NRowDisplay, 1);
				}
				else if (tableaufrom == 5) {
					S5.MoveCardFT(SelectFoundation(to, Foundation1, Foundation2, Foundation3, Foundation4), 'F', NRowDisplay, 1);
				}
				else if (tableaufrom == 6) {
					S6.MoveCardFT(SelectFoundation(to, Foundation1, Foundation2, Foundation3, Foundation4), 'F', NRowDisplay, 1);
				}
				else {
					S7.MoveCardFT(SelectFoundation(to, Foundation1, Foundation2, Foundation3, Foundation4), 'F', NRowDisplay,1);
				}
			}
			else {
				while (true) {
					for (int i = 1; i <= 7; i++) {
						if (i != tableaufrom) {
							cout << "Press " << i << " to move the card to Tableau " << i << endl;
						}
					}
					cout << "Tableau Number: ";
					cin >> to;
					if (to < 8 && to > 0 && to != tableaufrom) {
						break;
					}
					else {
						cout << " Incorrect selection! \n Select once again " << endl;
					}
				}
				int CardSelection;
				if (tableaufrom == 1) {
					if (S1.DisplayNumberOfCards>1) {
						SelectCard(S1, CardSelection);
						S1.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, CardSelection);
					}
					else{
						S1.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
					}
				}
				else if (tableaufrom == 2) {
					if (S2.DisplayNumberOfCards>1) {
						SelectCard(S2, CardSelection);
						S2.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, CardSelection);
					}
					else {
						S2.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
					}
				}
				else if (tableaufrom == 3) {
					if (S3.DisplayNumberOfCards>1) {
						SelectCard(S3, CardSelection);
						S3.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, CardSelection);
					}
					else {
						S3.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
					}
				}
				else if (tableaufrom == 4) {
					if (S4.DisplayNumberOfCards>1) {
						SelectCard(S4, CardSelection);
						S4.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, CardSelection);
					}
					else {
						S4.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
					}
				}
				else if (tableaufrom == 5) {
					if (S5.DisplayNumberOfCards>1) {
						SelectCard(S5, CardSelection);
						S5.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, CardSelection);
					}
					else {
						S5.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
					}
				}
				else if (tableaufrom == 6) {
					if (S6.DisplayNumberOfCards>1) {
						SelectCard(S6, CardSelection);
						S6.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, CardSelection);
					}
					else {
						S6.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
					}
				}
				else {
					if (S7.DisplayNumberOfCards>1) {
						SelectCard(S7, CardSelection);
						S7.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, CardSelection);
					}
					else {
						S7.MoveCardFT(SelectTableau(to, S1, S2, S3, S4, S5, S6, S7), 'T', NRowDisplay, 1);
					}
				}
			}
		}
		if (S1.DisplayNumberOfCards>NRowDisplay){
			NRowDisplay = S1.DisplayNumberOfCards;
		}
		else if (S2.DisplayNumberOfCards>NRowDisplay) {
			NRowDisplay = S2.DisplayNumberOfCards;
		}
		else if (S3.DisplayNumberOfCards>NRowDisplay) {
			NRowDisplay = S3.DisplayNumberOfCards;
		}
		else if (S4.DisplayNumberOfCards>NRowDisplay) {
			NRowDisplay = S4.DisplayNumberOfCards;
		}
		else if (S5.DisplayNumberOfCards>NRowDisplay) {
			NRowDisplay = S5.DisplayNumberOfCards;
		}
		else if (S6.DisplayNumberOfCards>NRowDisplay) {
			NRowDisplay = S6.DisplayNumberOfCards;
		}
		else if (S7.DisplayNumberOfCards>NRowDisplay) {
			NRowDisplay = S7.DisplayNumberOfCards;
		}
		Result=GameResult(Foundation1, Foundation2, Foundation3, Foundation4, WastePileRotation);
		if (Result==1|| Result==-1){
			break;
		}
		cout << endl;
		GameDisplay(S1, S2, S3, S4, S5, S6, S7, Foundation1, Foundation2, Foundation3, Foundation4, WastePile,WastePileNumber, NRowDisplay, WastePileTop, WastePileRotation);
		cout << endl ;
	}
	cout << endl << endl << endl;
	if (Result == 1) {
		cout << "================ You Win :) ================"<<endl;
	}
	else {
		cout << "================Try next time ================" << endl;
	}
	system("pause");
	return 0;
}

