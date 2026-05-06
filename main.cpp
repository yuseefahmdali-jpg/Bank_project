 #include <iostream>
 #include<vector>
 #include<fstream>
 #include<iomanip>


using namespace std;
const string clintfilename="clints.txt";

enum Enmtransactions{eDeposit=1, eWithdraw=2,eTotalBalances=3,eMainMenue=4};

void sava_clint(string linclin){
    fstream myfil;
    myfil.open(clintfilename,ios::out|ios::app);
    if(myfil.is_open()){

        myfil<<linclin<<endl;

        myfil.close();
    }


}
string read_string(){
    cout<<"enter number clint : ";
    string x;
    cin>>x;
    return x;
}
struct clint{
    string Acco_number;
    string pincode;
    string name;
    string phone;
    double Balance;
    bool markfordelet=false;
};
clint read_clint(){
    clint c1;
    cout<<"\n";
    cout<<"pleas Enter clint Data : \n";
    cout<<"\n";
    cout<<"Enter Account number ? ";
    getline(cin>>ws,c1.Acco_number);
    cout<<"Enter Pincode ? ";
    getline(cin,c1.pincode);
    cout<<"Enter name ? ";
    getline(cin,c1.name);
    cout<<"Enter phone ? ";
    getline(cin,c1.phone);
    cout<<"Enter Balance ? ";
cin>>c1.Balance;
    cout<<"\n";
    return c1;
}
string record_string(clint c,string s="#//#"){
    string ct="";

    ct=c.Acco_number+s;
    ct+=c.pincode+s;
    ct+=c.name+s;
    ct+=c.phone+s;
    ct+=to_string(c.Balance);

    return ct;

}
vector<string> split_string(string s1,string delim="#//#"){

    vector<string> vc;
   // cout<<"\nyou string words are:\n\n";
    int pos=0;
    string word;

    while((pos=s1.find(delim))!=std::string::npos){
        word=s1.substr(0,pos);
        if(word!=""){
          //  cout<<word<<endl;
        vc.push_back(word);
        }
        s1.erase(0,pos+delim.length());
    }

    if(s1!=""){
        vc.push_back(s1);
        //cout<<s1<<endl;
    }
    return vc;
}
clint cut_strings(string line_string,string seperator="#//#"){
    vector<string> lin;
    lin=split_string(line_string,seperator);
    clint c1;
    c1.Acco_number=lin[0];
    c1.pincode=lin[1];
    c1.name=lin[2];
    c1.phone=lin[3];
    c1.Balance=stod(lin[4]);

 return c1;

}
void print_clin(clint c){
    cout<<"\n";
    cout<<"===============================================\n";
    cout<<"the following is the extracted clint record\n\n";
    cout<<"Accout number :"<<c.Acco_number<<endl;
    cout<<"Pin code      :"<<c.pincode<<endl;
    cout<<"Name          :"<<c.name<<endl;
    cout<<"Phone         :"<<c.phone<<endl;
    cout<<"account Balance :"<<c.Balance<<endl;
    cout<<"===============================================\n";
    cout<<"\n";
}
void add_new_clint(){
    clint c=read_clint();
    print_clin(c);
    sava_clint(record_string(c));

}
void add_clins(){

    char x;
    do{
        add_new_clint();
        cout<<"\n\nenter [y] new clin : ";
        cin>>x;
    }while(x== 'y');

}
vector<clint> shaw_in_file(){
    vector<clint> acn;
    fstream myfil;
    myfil.open(clintfilename,ios::in);
    string lin;
    if(myfil.is_open()){
        while(getline(myfil,lin)){
            clint c1=cut_strings(lin);

           acn.push_back(c1);
        }
        myfil.close();
    }
    return acn;
}

bool findclintbyaccountnumber(string accontnumber,vector<clint>& acn,clint& aa){


        for(clint& c1:acn){

            if(c1.Acco_number==accontnumber){

            aa=c1;
            return true;

            }
    }
    return false;

}
void printclintrecord(clint c1){

    cout<<"| "<<setw(15)<<left<< c1.Acco_number;
    cout<<"| "<<setw(10)<<left<<c1.pincode;
    cout<<"| "<<setw(40)<<left<< c1.name;
    cout<<"| "<<setw(12)<<left<< c1.phone;
    cout<<"| "<<setw(12)<<left<< c1.Balance;

}
void print_all_clint(vector<clint> c1){
    cout<<"\n\t\t\t\tclint list ( "<<c1.size()<<" ) clint ";
    cout<<"\n________________________________________________";
    cout<<"________________________________________________\n"<<endl;
    cout<<"| "<<left<<setw(15)<<"Accou Number";
    cout<<"| "<<left<<setw(10)<<"pin code";
    cout<<"| "<<left<<setw(40)<<"clint name";
    cout<<"| "<<left<<setw(12)<<"phone";
    cout<<"| "<<left<<setw(12)<<"balance";
    cout<<"\n________________________________________________";
    cout<<"________________________________________________\n"<<endl;



    for (clint c:c1){
        printclintrecord(c);
        cout<<endl;
    }
    cout<<"\n________________________________________________";
    cout<<"________________________________________________\n"<<endl;

}
bool foind_in_one_clint(string x ,vector<clint> &delclint){
    for(clint& c:delclint){

            if(c.Acco_number==x){
                    c.markfordelet=true;
            return true;
    }
    }
    return false;
}
vector<clint> save_clint_data_line( vector<clint> ct){
   fstream myfile;
   myfile.open(clintfilename,ios::out);
   string line;
   if(myfile.is_open()){
        for(clint c:ct){
            if(c.markfordelet==false){
               line= record_string(c);
                myfile<<line<<endl;
            }

        }

    myfile.close();
   }
   return ct;

}
bool delite_in_clint_accontnumber(string acc ,vector<clint> delclint){
    clint cn;
   if(findclintbyaccountnumber(acc,delclint,cn)){
    print_clin(cn);
    char z;
    cout<<"Are you sure you delete this clint ( "<<acc<<" )? y : ";
    cin>>z;
    if(z=='y'){
        foind_in_one_clint(acc,delclint);
    save_clint_data_line(delclint);
    delclint=shaw_in_file();

    print_all_clint(delclint);

cout<<"\nclint deleted successfully :) \n";
return  true;
    }
   }
    else
        {
        cout<<"\nclint is not foind :( \n";
    }
    return false;
}
clint updat_in_clint(string acc){
clint c1;
    c1.Acco_number=acc;
    cout<<"Enter Pincode ? ";
    getline(cin>>ws,c1.pincode);
    cout<<"Enter name ? ";
    getline(cin,c1.name);
    cout<<"Enter phone ? ";
    getline(cin,c1.phone);
    cout<<"Enter Balance ? ";
    cin>>c1.Balance  ;


    return c1;

}
bool updat_clint(string acc ,vector<clint> delclint){
    clint cn;
   if(findclintbyaccountnumber(acc,delclint,cn)){
    print_clin(cn);
    char z;
    cout<<"Are you sure you delete this clint ( "<<acc<<" )? y : ";
    cin>>z;
    if(z=='y'){


            for(clint & upct:delclint){


      if(upct.Acco_number==acc){

           upct= updat_in_clint(acc);
           break;
      }
    }


    save_clint_data_line(delclint);

    delclint=shaw_in_file();

    print_all_clint(delclint);

cout<<"\nclint deleted successfully :) \n";
return  true;
    }
   }
    else
        {
        cout<<"\nclint is not foind :( \n";
    }
    return false;
}
void shawmenue_screen(){
    system("cls");
    cout<<"========================================================\n";
    cout<<"\t\tMain menue screen \n";
    cout<<"========================================================\n";

    cout<<"\t\[1] Show client list.\n";
    cout<<"\t\[2] Add New client.\n";
    cout<<"\t\[3] Delete client.\n";
    cout<<"\t\[4] Update client Info.\n";
    cout<<"\t\[5] Find client.\n";
    cout<<"\t\[6] Transactions.\n";
    cout<<"\t\[7] Exit.\n";
    cout<<"========================================================\n";


}

void transactions_screen(){
     system("cls");
       cout<<"========================================================\n";
    cout<<"\t\tTransactions menue screen \n";
    cout<<"========================================================\n";

    cout<<"\t\[1] Deposit.\n";
    cout<<"\t\[2] Withdraw.\n";
    cout<<"\t\[3] Total Balances.\n";
    cout<<"\t\[4] Main Menue.\n";
    cout<<"========================================================\n";


}


bool findclint_crement_balance(string accontnumber,vector<clint>& acn){


        for(clint& c1:acn){

            if(c1.Acco_number==accontnumber){
             print_clin(c1);
             int num;
            cout<<"\nPlease enter deposit amount ? ";
            cin>>num;
            c1.Balance+=num;



            return true;

            }
    }
    return false;

}
bool findclint_in_crement_balance(string accontnumber,vector<clint>& acn){


        for(clint& c1:acn){

            if(c1.Acco_number==accontnumber){
             print_clin(c1);
             go:
             int num;
            cout<<"\nPlease enter deposit amount ? ";
            cin>>num;
            if(num<=c1.Balance){
            c1.Balance+=num*-1;
            }
            else{
                cout<<"Amount Exceeds the balance, you can withdraw up to :"<<c1.Balance;
                goto go;
            }

            return true;

            }
    }
    return false;

}

void Deposit(vector<clint> acn){
      cout<<"=================================\n";
    cout<<"\tDeposit screen\n";
    cout<<"=================================\n";



     // print_all_clint(acn);

      string x=read_string();
        if (findclint_crement_balance(x,acn)){


            save_clint_data_line(acn);
            cout<<"\nclint cremet successfully :) \n";


        }
        else{
            cout<<"\nclint is not foind :( \n";
        }
       // print_all_clint(acn);

}
void Withdraw(vector<clint> acn){
    cout<<"=================================\n";
    cout<<"\tWuthdraw screen\n";
    cout<<"=================================\n";
      print_all_clint(acn);
      string x=read_string();
        if (findclint_in_crement_balance(x,acn)){
            save_clint_data_line(acn);
            cout<<"\nclint cremet successfully :) \n";
        }
        else{
            cout<<"\nclint is not foind :( \n";
        }
        print_all_clint(acn);
}

void print_clint_total(clint c1){

    cout<<"| "<<setw(15)<<left<< c1.Acco_number;
    cout<<"| "<<setw(40)<<left<< c1.name;
    cout<<"| "<<setw(12)<<left<< c1.Balance;

}
void Total_Balances(vector<clint> c1){
    double total=0;
    cout<<"\n\t\t\t\tclint list ( "<<c1.size()<<" ) clint ";
    cout<<"\n________________________________________________";
    cout<<"________________________________________________\n"<<endl;
    cout<<"| "<<left<<setw(15)<<"Accou Number";
    cout<<"| "<<left<<setw(40)<<"clint name";
    cout<<"| "<<left<<setw(12)<<"balance";
    cout<<"\n________________________________________________";
    cout<<"________________________________________________\n"<<endl;
    for (clint c:c1){
            total+=c.Balance;
        print_clint_total(c);
        cout<<endl;
    }
    cout<<"\n________________________________________________";
    cout<<"________________________________________________\n"<<endl;


    cout<<"\t\t\t\tTotal Balances = "<<total<<endl;
}

void transactions(){
    Enmtransactions enm;
ment:

    vector<clint> c1=shaw_in_file();
    transactions_screen();
   // shawmenue_screen();
     // print_all_clint(c1);


        cout<<"Choose what do you want to do ? [1 to 4] ? ";
        int a;
        cin>>a;
        switch (a){
            case Enmtransactions::eDeposit:{
                t1:
                system("cls");
                Deposit(c1);

        cout<<"\nenter [1] go to token or any nember go to manue : ";
    cin>>a;
    if(a==1){
        goto t1;
    }
    else{
        goto ment;
    }

                 break;
            }

            case Enmtransactions::eWithdraw:{
                t2:
                system("cls");
                Withdraw(c1);

      cout<<"\nenter [2] go to token or any nember go to manue : ";
    cin>>a;
    if(a==2){
        goto t2;
    }
    else{
        goto ment;
    }

                 break;
            }
            case Enmtransactions::eTotalBalances:{
                t3:
                system("cls");
                Total_Balances(c1);
        cout<<"\nenter [3] go to token or any nember go to manue : ";
    cin>>a;
    if(a==3){
        goto t3;
    }
    else{
        goto ment;
    }
                 break;
            }
            case Enmtransactions::eMainMenue:{
                break;
            }

        }

}

void strartmanue(){
    vector<clint> c1=shaw_in_file();
menue:
    shawmenue_screen();
     // print_all_clint(c1);


        cout<<"Choose what do you want to do ? [1 to 7] ? ";
        int x;
        cin>>x;
    switch(x){


        case 1:{
            t1:
     system("cls");

    print_all_clint(c1);

    cout<<"enter [1] go to token or any nember go to manue : ";
    cin>>x;
    if(x==1){
        goto t1;
    }
    else{
        goto menue;
    }
    break;
        }
        case 2:{
            t2:
        system("cls");

        add_clins();

          cout<<"enter [2] go to token or any nember go to manue : ";
    cin>>x;
    if(x==2){
        goto t2;
    }
    else{
        goto menue;
    }
     break;
        }
        case 3:{
            t3:
            system("cls");
        string nm=read_string();
        delite_in_clint_accontnumber(nm,c1);

    cout<<"enter [3] go to token or any nember go to manue : ";
    cin>>x;
    if(x==3){
        goto t3;
    }
    else{
        goto menue;
    }
     break;
        }
        case 4:{
            t4:
        system("cls");
        string nm=read_string();
        updat_clint(nm,c1);

          cout<<"enter [4] go to token or any nember go to manue : ";
    cin>>x;
    if(x==4){
        goto t4;
    }
    else{
        goto menue;
    }
     break;
        }
        case 5:{
            t5:
        system("cls");
            clint newclint;
            string nm=read_string();

            if(findclintbyaccountnumber(nm,c1,newclint)){
                cout<<"\nclint is foind :) \n";
                print_clin(newclint);
            }
            else{
                cout<<"\nclint is not foind :( \n";
            }

              cout<<"enter [5] go to token or any nember go to manue : ";
    cin>>x;
    if(x==5){
        goto t5;
    }
    else{
        goto menue;
    }
     break;
        }
        case 6:{
            t6:
            system("cls");
            transactions();
            cout<<"enter [6] go to token or any nember go to manue : ";
    cin>>x;
    if(x==6){
        goto t6;
    }
    else{
        goto menue;
    }
             break;
        }
        case 7:{
            break;
        }
 break;
    }



}
int main()
{

  //  vector<clint> acn=shaw_in_file();
   // Total_Balances(acn);
    //Withdraw();
    strartmanue();


   //
   // updat_clint(nm,c1);

    /*
    if(foind_in_clin(cn)){
        print_clin(cn);
    }
    else{
        cout<<"dont foind :( ";
    }

*/




   // add_clins();

    //A123#//#123#//#yosf ahmd#//#744477788#//#50000
    //clint c1=read_clint();
    //print_clin(c);
   // cout<<record_string(c1,"#//#");
    return 0;
}
