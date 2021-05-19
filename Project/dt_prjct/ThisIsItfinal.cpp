#include<iostream>
#include <vector>
#include<algorithm>
#include<string>
#include<cassert>
#include<fstream>
#include<cmath>
using namespace std;
void Rate(int a)
{
	for(int i=0; i<a; i++)
	{
		cout<<"*";
	}
}
double toRad(double d){
return (d * M_PI)/180;
}
/*THis is the array list of type */
class Restaurants{
		string name;
		int rating;
	public:
	Restaurants(string i="City",int j=0)
	{
		name=i;
		rating=j;
	}
	void setName(string i)
	{
		name=i;
	}
	string getName()
	{
		return name;
	}
	void setRating(int r)
	{
		rating =r; 
		
	}	
	int getRating()
	{
		return rating;
	}
};
class City{
	private :
		string name;
		int x,y;
		
	public:
	vector <Restaurants> rt;	
	City(string i="City",int temp_x=0,int temp_y=0)
	{
		name=i;
		x=temp_x;
		y=temp_y;
	}
	
	void preset()
	{
		string iname=name;
		iname=iname+".txt";
		ifstream rin(iname.c_str());
		int temp_size;
		int rate;
		string n;
		
		if(rin.is_open())
		{
			rin>>temp_size;
			for(int i=0; i<temp_size; i++)
			{
				rin>>n;
				rin>>rate;
				Restaurants r(n,rate);
				this->rt.push_back(r);
			}
		}
		rin.close();
 	}
	void setName(string i,int temp_x,int temp_y)
	{
		name=i;
		x=temp_x;
		y=temp_y;
	}
	string getCityName()
	{
		return name;
	}
    int getXCoordinate()
	{
		return x;
	}
	int getYCoordinate()
	{
	return y;
	}	
	void setRestaurants()
	{
		    string n;
			int rate;
			cout<<"\tRestaurant Name: ";
			cin.ignore();
			getline(cin, n);
			cout<<"\t\tInput ratings(1-5): ";
			cin>>rate;
			while(rate>5 && rate<0)
			{
				cout<<"Rating is between 0 and 5";
				cin>>rate;
			}
			Restaurants r(n,rate);
			this->rt.push_back(r);
			cout<<"\tRestaurant Added...\n\n";
			}
	void showRestaurant()
		{
			cout<<"\n\tRestaurants in "<<name<<" city\n";
			cout<<"Restaurants:\n";
			for (int i=0; i<rt.size(); i++)
			{
				cout<<rt.at(i).getName();
				cout<<"\t";
				Rate(rt.at(i).getRating());
				cout<<endl;
			}
		}
	void deleteRestaurant()
		{
			string n;
			int x,y;
			int count=0;
			
			int c;
			cout<<"\n\t1. Delete via Name ";
			cout<<"\n\t2. Return to Main Menu";
			cout<<"\n\tChoose Option : ";
			cin>>c;

			switch(c)
			{
				case 1:
					cout<<"Restaurant Name: ";
					cin.ignore();
					getline(cin, n);
					for(int i=0; i<rt.size(); i++)
					{
						if(rt.at(i).getName()==n)
						{
							rt.erase(rt.begin() + i);
							cout<<"\tRestaurant Deleted!\n";
							count++;
						}
						
					}
					if(count==0)
					{
						cout<<"There is no restaurant called "<<n;	
					}
					break;
					
				case 2:
					return;
				default:
					cout<<"Invalid Option!!! Try Again!!!";
					
			}
			
		}
		
		~City()
		{
			string fname=getCityName();
			fname=fname+".txt";
			ofstream rout(fname.c_str());
			
			if(rout.is_open())
			{
				rout<<rt.size()<<"\n";
				for(int i=0; i<rt.size(); i++)
				{
					cout<<rt.at(i).getName()<<" "<<rt.at(i).getRating()<<endl;
				}
			}
			rout.close();
		}		
};

class CityList{
  private:
  void operator =(const CityList&) {}
  CityList (const CityList&) {}
  public:
  CityList(){}
};
class CityAlist: public CityList{
  private:
  int maxSize;
  int listSize;
  int curr;
  City* listArray;
  public:
  CityAlist(){
    maxSize =100;
    listSize=curr=0;
    listArray=new City[maxSize];
  }
  ~CityAlist() { delete [] listArray;}
  void insert(const City& it){
    for(int i=listSize; i>curr; i--)
      listArray[i]=listArray[i-1];
    listArray[curr]=it;
    listSize++;
  }
  void append(const City& it)
  {
    listArray[listSize++]=it;
  }
  City remove()
  {
    City it=listArray[curr];
    for(int i=curr;i<listSize-1;i++)
    {
      listArray[i]=listArray[i+1];
    }
    listSize--;
    return it;
  }
  void moveToPos(int pos){
    curr=pos;
  }
  int getListSize()const
  {
    return listSize;
  }
  int getCurrentPos() const
  {
    return curr;
  }
  const City& getValue() const
  {
    return listArray[curr];
  }
  void moveToStart ()
  {
  	curr=0;
  }
  void moveToEnd()
  {
  	curr=listSize;
  }
  void swap(City *a,City *b)
   {
   City temp;
   temp=*a;
   *a=*b;
   *b=temp;
   }
  int binSearchName(string name)
  {
  	transform(name.begin(), name.end(), name.begin(), ::toupper);// convert the string we are looking for to upper case
	int first=-1;
  	int last=listSize; //first and last are beyond array bounds
  	int middle;
  	int position=-1;
  	while(first+1 != last) //keep checking while found is true and if first is less or equal to the last.
	{
		middle=(first+last)/2;
        if(name<listArray[middle].getCityName())
        {
        	last=middle;
		}
		if(name==listArray[middle].getCityName())
        {
        	return middle;
		}
		if(name>listArray[middle].getCityName())
        {
        	first=middle;
		}
	}
	return position;
  }
 void insertion_sort()
{
  for(int i=1;i<listSize;i++)
  {
     for(int j=i;((j>0) && (listArray[j].getCityName() < listArray[j-1].getCityName()));j--)
     {
     	swap(&listArray[j],&listArray[j-1]);
	 }
        
  }
}

void inssort2(int n,int incr)
{
  for(int i=incr;i<n;i+=incr)
  {
  	for(int j=i; ((j>=incr) &&  (listArray[j].getCityName() < listArray[j-incr].getCityName())); j-=incr)
  	{
  		swap(&listArray[j],&listArray[j-incr]);
	}
  }
}
void shellsort()
{
	for(int i=listSize/2; i>2; i/=2)
	{
		for(int j=0; j<i; j++)
		{
			inssort2(listSize-j,i);
		}
	}
	inssort2(listSize,1);

}

  void printCityName()
  {
  	  cout<<"The Current City's name is "<<listArray[curr].getCityName()<<endl;
  }
  void printCityCoD()
  {
  	cout<<"The City "<<listArray[curr].getCityName()<<" has co-ordinates ";
	cout<<"("<<listArray[curr].getXCoordinate()<<","<<listArray[curr].getYCoordinate()<<")"<<endl; 
  }
  
  void clear(){
    delete []listArray;
    listSize=curr=0;
    listArray=new City[maxSize];
  }
  
};
//The Cities class

//implementation of the city class
class Interface: public CityAlist
{
				
	public:
		CityAlist myCities;
		Interface()
		{
			int c;
			Preset();
			cout<<"\n_______________________________________________________________________________________________________________________\n";	
			cout<<"\n\t\t\t\tSTART MENU\t\t\n";
			cout<<"_______________________________________________________________________________________________________________________";	
	
			
			cout<<"\n\n\t1. Start";
			cout<<"\n\n\n\n\t0. Exit Application";
	
			do{
				cout<<"\n\n\tInput: ";
				cin>>c;
				switch(c)
				{
					case 1:
						admin();
						break;
		
					case 0:
						break;
					default:
						cout<<"Invalid input!";
				}
			}
			while(c!=0);
		}
		
		void Preset()
		{
			string n;
			int x,y;
			cout<<".....\n";
			ifstream in("Cities.txt");
			int temp_num;
			in>>temp_num;
			
			if(in.is_open())
			{
				for(int i=0; i<temp_num; i++)
				{
				
					in>>n;
					transform(n.begin(), n.end(), n.begin(), ::toupper);
					in>>x;
					in>>y;
					City nw(n,x,y);
					myCities.insert(nw);
				}
			}
			in.close();
			for(int i=0; i<temp_num; i++)
				{
					myCities.moveToPos(i);
					City x= myCities.getValue();
					x.preset();
				}
			myCities.shellsort();
			
		}
	
		void addCity()
		{
			string n;
			int x,y;	
			cout<<"\n\tCity Name : ";
			cin.ignore();
			getline(cin, n);
			transform(n.begin(), n.end(), n.begin(), ::toupper);
			cout<<"\n\tX-Coordinate : ";
			cin>>x;
			getchar();
			cout<<"\n\tY-Coordinate : ";
			cin>>y;
			City nw = City(n,x,y);
			myCities.insert(nw);
			myCities.insertion_sort();
			cout<<"\n\tCity added...";
	
			
		}
		
		void deleteCity()
		{
			string n;
			int x,y;
			int count=0;
			
			int c;
			cout<<"\n\t1. Delete via Coordinates";
			cout<<"\n\t2. Delete via Name ";
			cout<<"\n\t3. Return to Main Menu";
			cout<<"\n\tChoose Option : ";
			cin>>c;
			
			switch(c)
			{
				case 1:
						cout<<"Input x-coordinates: ";
					cin>>x;
					cout<<"Input y-coordinates: ";
					cin>>y;
					bool cityFound;
					for(int i=0; i<myCities.getListSize(); i++)
					{
						bool cityFound= false;
						myCities.moveToPos(i);
						City a;
						a=myCities.getValue();
						if(a.getXCoordinate()==x && a.getYCoordinate()==y)
						{
							City b;
							b=myCities.remove();
							cout<<"The City "<<b.getCityName()<<" has been deleted "<<endl;
							return;
						}
					}
					if(!cityFound)
					{
						cout<<"There is no City corresponding to ("<<x<<","<<y<<")\n";	
					}
					break;
					
				case 2:
					cout<<"City Name: ";
					cin.ignore();
					getline(cin, n);
					int a;
					a=myCities.binSearchName(n);
					if(a==-1)
					{
						cout<<"There is no city called "<<n;	
					}
					else
					{
						myCities.moveToPos(a);
						City b;
						b=myCities.remove();
						cout<<"The City "<<b.getCityName()<<" has been deleted "<<endl;
					}
					break;
				case 3:
					return;
				default:
					cout<<"Invalid Option!!! Try Again!!!";	
			}
			
		}

		void viewCities()
		{
			cout<<"Cities are:\n";
			for (int i=0; i<myCities.getListSize(); i++)
			{
				myCities.moveToPos(i);
				myCities.printCityCoD();
			}
		}
		
		int changeCity()
		{
			cout<<"\n\n\tWhich City's restaurants do you want to edit: \n";
			
			cout<<"\n\t1. Select city via Coordinates";
			cout<<"\n\t2. Select city via Name ";
			cout<<"\n\t3. Return to Main Menu";
			
			int x,y,count,indiex=-1;
			string n;
			
			do{
				count=0;
				cout<<"\n\n\tChoose Option : ";
				int c;
				cin>>c;
				
				switch(c)
				{
					case 1:
					cout<<"Input x-coordinates: ";
					cin>>x;
					cout<<"Input y-coordinates: ";
					cin>>y;
					
					for(int i=0; i<myCities.getListSize(); i++)
					{
						myCities.moveToPos(i);
						City a;
						a=myCities.getValue();
						if(a.getXCoordinate()==x && a.getYCoordinate()==y)
						{
						    indiex=i;
						}
					}
					
					if(indiex !=-1)
					{
						return indiex;
					}
					cout<<"There is no City corresponding to ("<<x<<","<<y<<")\n";
					break;
					
				case 2:
					cout<<"City Name: ";
					cin.ignore();
					getline(cin, n);
					int indiex;
					indiex=myCities.binSearchName(n);
					if(indiex!=-1)
					{
						return indiex;	
					}
					cout<<"There is no city called "<<n;
					
					break;
					
				case 3:
					admin();
					break;
					
				default:
					cout<<"\nInvalid Option!!! Try Again!!!";	
			}
			}while(count==0);
		}
		
		void viewall()
		{
			int i;
			
			for(i=0; i<myCities.getListSize(); i++)
			{
				myCities.moveToPos(i);
				myCities.printCityCoD();
				City x= myCities.getValue();
				x.showRestaurant(); 
				cout<<endl<<endl;
			}
		}
		void getDistance()
		{
			double x;double y;double a ; double b;
			cout<<"Enter coordinates of city 1  :";
			cin>>x>>y;
			cout<<"Enter coordinates of city 2 : ";
			cin>>a>>b;
			
			
			double theta = b- y;
			double distance=acos(sin(x) * sin(a) + cos(x) * cos(a) * cos(theta));
			cout<<"The distance between city1"<<" and city 2"<<" is "<<distance<<endl;
		}
		double distance( double x,  double y, double a, double b)
		{
                     
		 x = toRad(x);
         y = toRad(y);
         a = toRad(a);
         b = toRad(b);
        }

		void Reditor()
		{
			cout<<"\n_______________________________________________________________________________________________________________________\n";	
			cout<<"\n\t\t\t\tRESTAURANT EDITOR MENU\t\t\n";
			cout<<"_______________________________________________________________________________________________________________________";	
	
			int op;
			int i=changeCity();
			myCities.moveToPos(i);
			City b=myCities.getValue();
			
			do{
				cout<<"\n\n\t"<<b.getCityName()<<" City Restaurant Database";
				cout<<"\n\n\t1. Insert Restaurant";
				cout<<"\n\n\t2. Delete Restaurant";
				cout<<"\n\n\t3. View All Restaurants";
				cout<<"\n\n\t0. Admin Menu";

				cout<<"\n\n\tChoose Option : ";
				cin>>op;
				switch(op){
					case 1:
						cout<<"\n\tInsert Record\n";
						b.setRestaurants();
						break;
					case 2:
						cout<<"\n\tDelete Record\n";
						b.deleteRestaurant();
						break;
					case 3:
						cout<<"\n\tViewing Records\n";
						b.showRestaurant();
						break;
					case 0:
						admin();
						break;
					default:
						cout<<"\nInvalid Option!!! Try Again!!!";
					}
				}while(op!=0);
			}		

			void admin()	
			{
				cout<<"\n_______________________________________________________________________________________________________________________\n";	
				cout<<"\n\t\t\t\tMAIN MENU\t\t\n";
				cout<<"_______________________________________________________________________________________________________________________";	
	
				int op;
				do{
				cout<<"\n\n\t1. Insert City";
				cout<<"\n\n\t2. Delete City";
				cout<<"\n\n\t3. View All Cities";
				cout<<"\n\n\t4. Restaurant Editor";
				cout<<"\n\n\t5. View all Data";
				cout<<"\n\n\t6. Get distance between two Citiesl";
				cout<<"\n\n\t0. Main Menu";

				cout<<"\n\n\tChoose Option : ";
				cin>>op;
				switch(op){
					case 1:
						cout<<"\n\tAdd City\n";
						addCity();
						break;
					case 2:
						cout<<"\n\tDelete Record\n";
						deleteCity();
						break;
					case 3:
						cout<<"\n\tViewing Records\n";
						viewCities();
						break;
					case 4:
						cout<<"\n\t***Restaurant Editor***\n\n";
						Reditor();
						break;
					case 5:
						cout<<"Viewing all data\n\n";
						viewall();
						break;
					case 6:
						cout<<"Get distance between two Cities\n\n"	;
						getDistance();
						break;
					case 0:
						Interface();
						break;
					default:
						cout<<"Invalid Option!!! Try Again!!!";
					}
				}while(op!=0);
			}
			
		~Interface()
		{
			string n;
			int x,y;
			cout<<".....\n";
			ofstream out("Cities.txt");
			int temp_num=myCities.getListSize();
			out<<temp_num<<"\n";
			
			if(out.is_open())
			{
				for(int i=0; i<temp_num; i++)
				{
					myCities.moveToPos(i);
					City x= myCities.getValue();
					out<<x.getCityName()<<" "<<x.getXCoordinate()<<" "<<x.getYCoordinate()<<endl;
				}
			}
			out.close();
			cout<<"\nApplication closed";
		}
};


int main()
{
	cout<<"_______________________________________________________________________________________________________________________";
	cout<<"\n_______________________________________________________________________________________________________________________\n";
	cout<<"\n\t\t\t\t\tCITY-RESTAURANT DATABASE\t\t\n";
	cout<<"_______________________________________________________________________________________________________________________";	
	cout<<"\n_______________________________________________________________________________________________________________________";	
	cout<<"\n\n\tAccessing Database...";
	Interface();

	return 0;
		
}
