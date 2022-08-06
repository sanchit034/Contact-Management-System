#include<iostream>
#include<string>
#include<vector>
using namespace std;


int listSize=0;
class contact
{
private:
    string name;
    vector<string> number;
    contact* next;
public:
    contact(string, vector<string>);
    contact(string, vector<string>, contact*);
    contact* addContact();
    void display();
    contact* delContact(string);
    void searchContactByName(string);
    void searchContactByNumber(string);
    contact* clearContactList();
};



void menu(){
    cout<<"------------------------------------------------"<<endl;
    cout<<"|               ***Phone Book***               |"<<endl;
    cout<<"|            Press 1 to add contact            |"<<endl;
    cout<<"|          Press 2 to delete contact           |"<<endl;
    cout<<"|         Press 3 to display contact           |"<<endl;
    cout<<"|      Press 4 to Search contact by name       |"<<endl;
    cout<<"|     Press 5 to Search contact by number      |"<<endl;
    cout<<"|      Press 6 to delete all the contact       |"<<endl;
    cout<<"------------------------------------------------"<<endl;
}




int main(){
    contact* head=NULL;
    string operation;
    string toOperate;
    while(1){
        menu();
        cin>>operation;
        switch (operation[0])
        {
        case '1':
            head=head->addContact();
            cout<<endl;
            break;
        case '2':
            cout<<"Enter to contact name to be deleted:";
            cin>>toOperate;
            head=head->delContact(toOperate);
            break;
        case '3':
            head->display();
            break;
        case '4':
            cout<<"Enter the name of contact to be searched: ";
            cin>>toOperate;
            head->searchContactByName(toOperate);
            cout<<endl;
            break;
        case '5':
            cout<<"Enter the number of contact to be searched: ";
            cin>>toOperate;
            head->searchContactByNumber(toOperate);
            cout<<endl;
            break;
        case '6':
            head=head->clearContactList();
            cout<<"All contacts are deleted, ";
            head->display();
            break;
        default:
            cout<<"Press a key from 1-6"<<endl<<endl;
        }
        cout<<endl;
    }
    return 0;
}



contact::contact(string first, vector<string> second){
    name=first;
    number=second;
    next=NULL;
}

contact::contact(string first, vector<string> second, contact* third){
    name=first;
    number=second;
    next=third;
}

contact* contact::addContact(){
    string name, mobile;
    vector<string> number;
    cout<<"Enter Name: ";
    cin>>name;
    cout<<"Press / to update."<<endl;
    cout<<"Enter mobile number: ";
    cin>>mobile;
    while(mobile!="/"){
        number.push_back(mobile);
        cout<<"Enter mobile number: ";
        cin>>mobile;
    }
    if(this==NULL){
        contact* head=new contact(name, number);
        listSize++;
        return head;
    }
    if(this->name==name){
        cout<<"Contact with this name already exist. Please change the name."<<endl;
        return this;
    }
    else if(this->name>name){
        contact* ptr=new contact(name, number, this);
        listSize++;
        return ptr;
    }
    else{
        contact* temp=this;
        while(temp->next){
            if(name==temp->next->name){
                cout<<"Contact with this name already exist. Please change the name."<<endl;
                return this;        
            }
            else if(name<temp->next->name){
                break;
            }
            temp=temp->next;
        }
        contact* ptr=new contact(name, number, temp->next);
        listSize++;
        temp->next=ptr;
    }
    return this;
}

void contact::display(){
    contact* head=this;
    int i,n,count=0;
    if(head==NULL){
        cout<<"Contact list is Empty."<<endl;
        return ;
    }
    cout<<"Total contact present in the list are "<<listSize<<endl<<endl;
    while(head!=NULL){
        cout<<++count<<") ";
        cout<<"Name: "<<head->name<<endl;
        n=head->number.size();
        for(i=0; i<n; i++){
            cout<<"Mobile Number "<<i+1<<": "<<head->number[i]<<endl;
        }
        head=head->next;
        cout<<endl;
    }
    cout<<endl;
}

contact* contact::delContact(string toDelete){
    contact* head=this;
    if(head==NULL){
        cout<<"Contact List is Empty."<<endl<<endl;
        return NULL;
    }
    if(head->name==toDelete){
        contact* ptr=head->next;
        delete head;
        cout<<toDelete<<" is deleted from list."<<endl<<endl;
        listSize--;
        return ptr;
    }
    while(head->next){
        if(head->next->name==toDelete){
            contact* ptr=head->next;
            head->next=ptr->next;
            delete ptr;
            cout<<toDelete<<" is deleted from list."<<endl<<endl;
            listSize--;
            return this;
        }
        head=head->next;
    }
    cout<<toDelete<<" is not in contact list."<<endl<<endl;
    return this;
}

void contact::searchContactByName(string toSearch){
    contact* ptr=this;
    int i, n, index=0, found=0;
    while(ptr){
        index++;
        if((ptr->name).find(toSearch)+1){
            cout<<index<<") ";
            cout<<"Name: "<<ptr->name<<endl;
            n=ptr->number.size();
            for(i=0; i<n; i++){
                cout<<"Mobile Number "<<i+1<<": "<<ptr->number[i]<<endl;
            }
            found=1;
        }
        ptr=ptr->next;
    }
    if(found==0)
        cout<<"Contact not found."<<endl;
}

void contact::searchContactByNumber(string toSearch){
    contact* ptr=this;
    int i, n, index=0, found=0, printName=1;
    while(ptr){
        index++;
        n=ptr->number.size();
        printName=1;
        for(i=0; i<n; i++){
            if((ptr->number[i]).find(toSearch)+1){
                if(printName)
                    cout<<index<<") "<<"Name: "<<ptr->name<<endl;
                printName=0;
                found=1;
                cout<<"Mobile Number: "<<ptr->number[i]<<endl;
            }
        }
        ptr=ptr->next;
    }
    if(found==0)
        cout<<"Contact not found."<<endl;
}

contact* contact::clearContactList(){
    contact* head=this, *ptr;
    while(head){
        ptr=head;
        head=head->next;
        delete ptr;
    }
    return NULL;
}
