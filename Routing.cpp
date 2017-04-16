#include <iostream> //500:34 5000(120) 
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include<queue>
using namespace std;
vector<int> start;
vector<int> end;
vector<int> visited;
vector<int> dirt;
vector<int>nodes[10000];//
queue<int> que;
struct map
{
	int point1;
	int point2;
};
struct map mapping[10000];// memory maybe 10000 3600莱赣临 
void judge(int sx,int sy,int ex,int ey,int s);
int main(int argc, char **argv)   
{
	start.resize(8000);
	end.resize(8000);
	visited.resize(8000);
	dirt.resize(8000);
    if(argc != 3)
    {
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
        system("pause");
    }
    // open the input file
    fstream fin;
    fin.open(argv[1], fstream::in);
    if(!fin.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }
    fstream fout;
    fout.open(argv[2],fstream::out);
	if(!fout.is_open())
    {
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }
    // parse the input file
    cout << "======================" << endl;
    cout << "        Parser        " << endl;
    cout << "======================" << endl;

    char buffer[100];
    fin >> buffer; //0
    fin >> buffer; //5
    int gridx = atoi(buffer); 
    fin >> buffer;//5
    int gridy = atoi(buffer); 
    fin >> buffer;//0
    fin >> buffer;//3
	int capacity = atoi(buffer); 
	fin >> buffer;//0
	fin >> buffer;//0
    fin >> buffer;//10
    int net = atoi(buffer);
    cout << "grid:" << gridx << "\t" << gridy<< endl;
    cout << "capacity:" << capacity<< endl;
    cout << "net:" << net<< endl;
    for(int s = 0; s < net; ++s) // numChord / 2 =6 net
    {
    	fin >> buffer;
    	fin >> buffer;
    	int x=atoi(buffer);
    	fin >> buffer;
    	int y=atoi(buffer);
   		start[s] =y*gridx + x;		
    	fin >> buffer;
    	int a=atoi(buffer);
    	fin >> buffer;
    	int b=atoi(buffer);
		end[s] =b*gridx + a;  	
		judge(x,y,a,b,s);
		cout <<"dirts:"<< s  <<" " << dirt[s] <<endl;
	}
	// Adjacency
	for (int y=0 ; y<gridx ; ++y)
		for (int x=0 ; x<gridx ; ++x)
			{
				int num=y*gridx + x;
				nodes[num].push_back(num);
				mapping[num].point1=x;
				mapping[num].point2=y; //num计 4 5 15..... 
				if((y-1)>=0)
					{			
						int num1=(y-1)*gridx + x;
						nodes[num].push_back(num1);
					}
				if((x-1)>=0)
					{
						int num2=y*gridx + (x-1);
						nodes[num].push_back(num2);
					}	
				if((x+1)<gridx)
					{
						int num3=y*gridx + (x+1);
						nodes[num].push_back(num3);
					}
				if((y+1)<gridx)
					{
						int num4=(y+1)*gridx + x;
						nodes[num].push_back(num4);
					}
			}
		for(int i=0;i<gridx * gridy;++i)
			{
			
				for(vector<int>::iterator it=nodes[i].begin(); // it夹 膀セ块nodes 眖繷Ю 
					it!=nodes[i].end();++it)
				{
					cout<<(*it)<<"-->";
				}
				cout<<"NULL"<<endl;
			}	
	//
	int bcd=0;
	for(int i=0 ; i<net ; ++i) //材n舱计  net
	{
		for(int p=0;p< gridx*gridy;++p)
			visited[p]=0;
		int count=0;
		int asd=0;
		int path=0;
		int jump=0;
		int  spaceman=0;
		int spacecount =0;
		que.push(start[i]);   //3
		visited[start[i]]=-1;// 簿 
		while(!que.empty())
			{	
				count=count+1;
			 	int front = que.front();
				que.pop();
				for(vector<int>::iterator it=nodes[front].begin();it!=nodes[front].end();++it)   //тnode狟ね endぃ琌挡 τ琌挡 ノㄓ讽挡 
					{
						if(visited[*it]==0) //*it 块贝砐计  0ゼ砆贝 
							{
								asd=asd+1;
								if(count==1)  //only材Ω 
									{
										visited[*it]=1; //材Ω碞т沧翴 
										if(*it==end[i]) //т沧翴 
											{	
												fout  <<i<<" "  <<visited[end[i]] <<endl ;   //  net totla path visited[end[i]]  global常ノ 
												fout <<mapping[start[i]].point1<<" "<<mapping[start[i]].point2<<" " ;
												jump=jump+1;
												if(jump%2==0)
													fout <<endl;
												fout <<mapping[end[i]].point1<<" "<<mapping[end[i]].point2<<" " ;
												jump=jump+1;
												if(jump%2==0)
													fout <<endl;																																					
											}
									}							
								else 
									{
								  		visited[*it] =visited[front]+1;
										if(*it==end[i])//т沧翴 
											{	
												fout <<i <<" "  <<visited[end[i]]  <<endl ;
												spaceman= start[i];    	
									    		fout <<mapping[start[i]].point1<<" "<<mapping[start[i]].point2<<" " ; //癬翴 
									    		jump=jump+1;
									    		while(spacecount !=visited[end[i]]) //单ボт 
												{ 
													switch(	dirt[i])
														{ 
															case 1: //┕オ ┕オ ┕ 
																{					
																	if(mapping[end[i]].point1   != mapping[spaceman].point1)
																	  { 
																    		spaceman=spaceman-1; //adjust 沧翴砆э-1 
												    						fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    						jump=jump+1;
												    						if(jump %2 ==0) //案计 
												    							{								
												    								fout << endl;
												    								if(jump!=2 * visited[end[i]] )
												    									{ 
																							fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																							jump=jump+1;
																						}	 
												    				  			}
												    				  			
										    								spacecount=spacecount+1;		//ǐ笵visted 1 countxx1	
																	  }
																	 else if(mapping[end[i]].point2 != mapping[spaceman].point2)
																		 {
																			spaceman=spaceman+gridx; //adjust 沧翴砆э-1 
												    						fout<< mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    						jump=jump+1;
												    							if(jump %2 ==0) //案计 
												    								{								
												    									fout << endl;
												    									if(jump!=2 * visited[end[i]] )
												    										{ 
																								fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																								jump=jump+1;
																							} 
												    								}
										    								spacecount=spacecount+1;		//ǐ笵visted 1 countxx1
																	 	}							 	
																	break;	 
																}
									
															case 2: //┕ 
																{				
																    spaceman=spaceman+gridx; //adjust 沧翴砆э-1 
												    				fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ; //path 1 秨﹍   space⊿? 
												    				jump=jump+1;
												    				if(jump %2 ==0) //案计 
												    					{								
												    						fout << endl;
												    						if(jump!=2 * visited[end[i]] )
												    						{ 
																				fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																				jump=jump+1;
																			} 
												    					}
												    			
										    						spacecount=spacecount+1;		//ǐ笵visted 1 countxx1		
																	break;	 
																}
															case 3: //┕ ┕ ┕ 
																{					
																	if(mapping[end[i]].point1   != mapping[spaceman].point1)
																	  { 
																    		spaceman=spaceman+1; //adjust 沧翴砆э-1 
												    						fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    						jump=jump+1;
												    						if(jump %2 ==0) //案计 
												    							{								
												    								fout << endl;
												    								if(jump!=2 * visited[end[i]] )
												    									{ 
																							fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																							jump=jump+1;
																						}	 
												    				  			}
												    				  			
										    								spacecount=spacecount+1;		//ǐ笵visted 1 countxx1	
																	  }
																	 else if(mapping[end[i]].point2 != mapping[spaceman].point2)
																		 {
																			spaceman=spaceman+gridx; //adjust 沧翴砆э-1 
												    						fout<< mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    						jump=jump+1;
												    							if(jump %2 ==0) //案计 
												    								{								
												    									fout << endl;
												    									if(jump!=2 * visited[end[i]] )
												    										{ 
																								fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																								jump=jump+1;
																							} 
												    								}
										    								spacecount=spacecount+1;		//ǐ笵visted 1 countxx1
																	 	}							 	
																	break;	 
																}
									
															case 4: //┕オ 
																{					
																    spaceman=spaceman-1; //adjust 沧翴砆э-1 
												    				fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    				jump=jump+1;
												    				if(jump %2 ==0) //案计 
												    					{								
												    						fout << endl;
												    						if(jump!=2 * visited[end[i]] )
												    						{ 
																				fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																				jump=jump+1;
																			} 
												    					}
												    			
										    						spacecount=spacecount+1;		//ǐ笵visted 1 countxx1			 
										    						break;
																}	
															case 5: //┕ 
																{					
																    spaceman=spaceman+1; //adjust 沧翴砆э-1 
												    				fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    				jump=jump+1;
												    				if(jump %2 ==0) //案计 
												    					{								
												    						fout << endl;
												    						if(jump!=2 * visited[end[i]] )
												    						{ 
																				fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																				jump=jump+1;
																			} 
												    					}
												    			
										    						spacecount=spacecount+1;		//ǐ笵visted 1 countxx1			 
										    						break;
																}		
															case 6: //┕オ ┕オ ┕ 
																{					
																	if(mapping[end[i]].point1   != mapping[spaceman].point1)
																	  { 
																    		spaceman=spaceman-1; //adjust 沧翴砆э-1 
												    						fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    						jump=jump+1;
												    						if(jump %2 ==0) //案计 
												    							{								
												    								fout << endl;
												    								if(jump!=2 * visited[end[i]] )
												    									{ 
																							fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																							jump=jump+1;
																						} 
												    							}
												    			
										    								spacecount=spacecount+1;		//ǐ笵visted 1 countxx1	
																	  }
																	 else if(mapping[end[i]].point2 != mapping[spaceman].point2)
																	 {
																			spaceman=spaceman-gridx; //adjust 沧翴砆э-1 
												    						fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    						jump=jump+1;
												    						if(jump %2 ==0) //案计 
												    							{								
												    								fout << endl;
												    								if(jump!=2 * visited[end[i]] )
												    									{ 
																							fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																							jump=jump+1;
																						} 
												    							}
												    			
										    								spacecount=spacecount+1;		//ǐ笵visted 1 countxx1	
																	  }			 	
																	break;	 
																}
															case 7: //┕ 
																{					
																    spaceman=spaceman-gridx; //adjust 沧翴砆э-1 
												    				fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    				jump=jump+1;
												    				if(jump %2 ==0) //案计 
												    					{								
												    						fout << endl;
												    						if(jump!=2 * visited[end[i]] )
												    						{ 
																				fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																				jump=jump+1;
																			} 
												    					}
												    			
										    						spacecount=spacecount+1;		//ǐ笵visted 1 countxx1		
																	break;	 
																}
															case 8: //┕ ┕ ┕ 
																{					
																	if(mapping[end[i]].point1   != mapping[spaceman].point1)
																	  { 
																    		spaceman=spaceman+1; //adjust 沧翴砆э-1 
												    						fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    						jump=jump+1;
												    						if(jump %2 ==0) //案计 
												    							{								
												    								fout << endl;
												    								if(jump!=2 * visited[end[i]] )
												    									{ 
																							fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																							jump=jump+1;
																						} 
												    							}
										    								spacecount=spacecount+1;		//ǐ笵visted 1 countxx1	
																	  }
																	 else if(mapping[end[i]].point2 != mapping[spaceman].point2)
																	 {
																			spaceman=spaceman-gridx; //adjust 沧翴砆э-1 
												    						fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
												    						jump=jump+1;
												    						if(jump %2 ==0) //案计 
												    							{								
												    								fout << endl;
												    								if(jump!=2 * visited[end[i]] )
												    									{ 
																							fout <<mapping[spaceman].point1<<" "<< mapping[spaceman].point2<<" " ;
																							jump=jump+1;
																						} 
												    							}
										    								spacecount=spacecount+1;		//ǐ笵visted 1 countxx1
																	 }							 	
																	break;	 
																}
															default:
																break;
														} 
												
												}	
											}																						
										}
									
								if(*it!=end[i]) 
									que.push(*it);	
							}
							
					}
			}
		
	}			

	system("pause");
    return 0;
	
}	
//function
void judge(int sx,int sy,int ex,int ey,int s)
	{
		if(ex<sx)   //オ场 
		{		
			if(ey>sy)
				dirt[s]=1;
			else if(ey==sy)
				dirt[s]=4;
			else if(ey<sy)
				dirt[s]=6;
		}
		else if(ex==sx) // 
		{
			if(ey>sy)
				dirt[s]=2;
			else if(ey<sy)
				dirt[s]=7;
		} 
		else if(ex>sx) //场 
		{ 
			if(ey==sy)
				dirt[s]=5;
			else if(ey<sy)
				dirt[s]=8;
			else if(ey>sy)
				dirt[s]=3;	
		}	
	}
