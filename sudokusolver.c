// Program to solve sudoku where size is between 3<=size<=10

//	NAME	 	: AKASH SRIVASTAVA
//	Roll no. 	: MT2014004
//	Project Name    : Sudoku Solver
//	Implemented Rules : All four rules

	

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
	void update(int a,int b,int d);
	void assign();
	int compare(int jam[3],int ja[3],int agh);
	void traverse();
	void cross();
	void candidatelist();
	void rule1();
	void rule2();
	void rule3();
	void rule4();
	void rule2_row();
	void rule2_box();
	void rule2_col();
struct list
{
	int candidate;
	struct list *next;
};
	int size;
	int notin[100][100];
	int arr[100][100];
	int see[100][100];
	struct list *headarray[100][100];
	
	struct list *node;
	struct list *node1,*node2;
	int count=0,candi=0;
	int check[100][100];
int main()
{
	int i,j,k;
	int l,m,n,o,bc,flag=0,count1=0,x=0,count2=0,row=0,count3=0,col=0,col2=0,prevcount=0,count5=0,size1=2,size2=3;
	int cancount=0,lk,lm,count11=0;
	
	int arr1[3],arr2[3],arr3[3];
	int ab,div1,div2,count10=0,initial=0,initial2=0,candicount=0,prevcount1=0;
	
	
	for(i=1;i<=size;i++)
	{
		for(j=1;j<=size;j++)
		{
			headarray[i][j]=NULL;	
		}
	}
	scanf("%d",&size);
	memset(check, 0, (sizeof check[0][0])*size*size);
	memset(notin, 0, (sizeof notin[0][0])*size*size);
	memset(see, 0, (sizeof see[0][0])*size*size);
	// taking sudoku input
	
	for(i=1;i<=(size*size);i++)
	{
		for(j=1;j<=(size*size);j++)
		{
			scanf("%d",&arr[i][j]);
			if(arr[i][j]==0)
			count++;
		}

	}
	
	
	traverse();		            // updating missing no matrix
	cross();	   	    	// crosshatching
	candidatelist();		// preparing candidate list
	rule1();			// rule1
	while(1)
	{
		prevcount1=count;
				    
		rule1();		    	// rule1
		rule2_box();			//rule2 for box
		rule2_row();			// rule2 column
		rule2_col();			// rule 2 for row
		rule1();	    		// rule 1				
		rule3();			// rule 3
		rule2_box();			//rule2 for box
		rule2_row();			
		rule2_col();		    
		rule4();			// rule 4
		if(prevcount1==count)
		break;
				    
	
	}		    
	
	for(i=1;i<=size*size;i++)
	{

		for(j=1;j<=size*size;j++)
		{
			printf("%d ",arr[i][j]);

		}
		printf("\n");
	}
	
return 0;

}
void update(int i,int j,int num)
{	
	int row,col,a,b,c,d,e,f,it;
	row=i-1;
	col=j-1;
	a=row/size;
	b=row%size;
	c=col/size;
	d=col%size;
	e=a*size+c;
	for(it=0;it<size*size;it++)
	{
		if(notin[e][it]==num)
		{
			notin[e][it]=0;
			break;
		}
	}
	
	
}

int compare(int arr1[3],int arr2[3],int size)
{
	
	int i,j,count1=0;
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(arr1[i]==arr2[j])
			count1++;
			
		}
	}
	if(count1==size)
	return 1;
	else
	return 0;
}


void assign()
{
	int i,j,k,count5=0,div1=0,div2=0,m;
	struct list *node1=NULL,*node2=NULL;
	for(i=1;i<=size*size;i++)
	{
		for(j=1;j<=size*size;j++)
		{
			
			
			if(see[i][j]==1 && arr[i][j]==0)
			{
				arr[i][j]=headarray[i][j]->candidate;
				free(headarray[i][j]);
				headarray[i][j]=NULL;
				for(k=1;k<=size*size;k++)
				{
					count5=0;
					node1=headarray[i][k];
					while(node1)
					{
						count5++;
						if(node1->candidate==arr[i][j] && count5==1)
						{
							
							see[i][k]--;
							headarray[i][k]=node1->next;
							free(node1);
							break;
						}
						else if(node1->candidate==arr[i][j] && count5!=1)
						{
							see[i][k]--;
							node2->next=node1->next;
							free(node1);
							break;
						}
						else
						{
							node2=node1;
							node1=node1->next;
						}
					}
				}
				for(k=1;k<=size*size;k++)
				{
					count5=0;
					node1=headarray[k][j];
					while(node1)
					{
						count5++;
						if(node1->candidate==arr[i][j] && count5==1)
						{
							
							see[k][j]--;
							headarray[k][j]=node1->next;
							free(node1);
							break;
						}
						else if(node1->candidate==arr[i][j] && count5!=1)
						{
							see[k][j]--;
							node2->next=node1->next;
							free(node1);
							break;
						}
						else
						{
							node2=node1;
							node1=node1->next;
						}
					}
				}
				div1=(i-1)/size;
				div2=(j-1)/size;
				for(k=(size*div1)+1;k<=(size*(div1+1));k++)
				{
					for(m=(size*div2)+1;m<=(size*(div2+1));m++)
					{
						count5=0;
						node1=headarray[k][m];
						while(node1)
						{
							count5++;
							if(node1->candidate==arr[i][j] && count5==1)
							{
							
								see[k][m]--;
								headarray[k][m]=node1->next;
								free(node1);
								break;
							}
							else if(node1->candidate==arr[i][j] && count5!=1)
							{
								see[k][m]--;
								node2->next=node1->next;
								free(node1);
								break;
							}
							else
							{
								node2=node1;
								node1=node1->next;
							}
						}
					}
				}
				
				count--;
				see[i][j]=0;
				update(i,j,arr[i][j]);
			}
		}
	}
}
void traverse()
{
	int i,j,k,l,m;
	int col2=0,col=0;
	int flag=0;
	int count2=0,count1=0,count3=0;
	for(i=0;i<size*size;i++)
	{
		col=0;
		for(j=1;j<=size;j++)
		{
			for(k=1;k<=size;k++)
			{

				if(arr[count2+j][count1+k]!=0)
				{
					check[i][col++]=arr[count2+j][count1+k];

				}
			}
		}

		col2=0;
		for(l=1;l<=size*size;l++)
		{
			flag=0;
			for(m=0;m<size*size;m++)
			{
				if(check[i][m]==l)
				{
				flag++;
				break;
				}
			}
			if(flag==0){
			notin[i][col2++]=l;
			}
		}
		count1=count1+size;
		if(count1==size*size)
		{
			count3++;
			count1=0;
			count2=count3*size;
		}


	}
}
void cross()
{
int prevcount=0,m,i,j,k,n,flag=0;
int count1=0,count2=0,row=0,count3=0,col=0,col2=0,cancount=0;
while(1)
{
	
	prevcount=count;
	count1=0,count2=0,row=0,count3=0,col=0,col2=0,flag=0,cancount=0;
	for(i=0;i<size*size;i++)
	{
		for(m=0;m<size*size;m++)
		{

			if(notin[i][m]==0)
			{
				if(i%size!=size-1 &&m==size*size-1)
					count1=count1+size;
				if(i%size==size-1 &&m==size*size-1)
				{
					count1=count1+size;
					if(count1==size*size)
					{
						count3++;
						count1=0;
						count2=count3*size;
					}
				}
			}
			else
			{
			cancount=0;
			for(j=1;j<=size;j++)
				{
				for(k=1;k<=size;k++)
					{
					flag=0;
					if(arr[count2+j][count1+k]==0)
						{

							for(n=1;n<=size*size;n++)
							{
								if((notin[i][m])==(arr[count2+j][n]))
								{
									flag=1;
									break;
								}
							}
							for(n=1;n<=size*size;n++)
							{
								if((notin[i][m])==(arr[n][count1+k]))
								{
									flag=1;
									break;
								}
							}

							if(flag==0)
							{
								cancount++;
								row=count2+j;
								col=count1+k;
							}


						}
					}
				}
			if(cancount==1)
				{
				arr[row][col]=notin[i][m];
				notin[i][m]=0;
				count--;

				}

			}



		}




	}
if(count==prevcount)
	break;

}
}
void candidatelist()
{
	int count1=0,count2=0,row=0,count3=0,col=0,col2=0,flag=0,cancount=0;
	int i,j,k;
	int m,n;

	
	for(i=0;i<size*size;i++)
	{
		
			for(j=1;j<=size;j++)
			{
				for(k=1;k<=size;k++)
				{
					
					
					if(arr[count2+j][count1+k]==0)
					{
						cancount=0;
						for(m=0;m<size*size;m++)
						{
							
							flag=0;
							if(notin[i][m]!=0)
							{
							
								for(n=1;n<=size*size;n++)
								{
									if((notin[i][m])==(arr[count2+j][n]))
									{
										flag=1;
										break;
									}
								}
								for(n=1;n<=size*size;n++)
								{
									if((notin[i][m])==(arr[n][count1+k]))
									{
										flag=1;
										break;
									}
								}

								if(flag==0)
								{
									cancount++;
									node=(struct list*)malloc(sizeof(struct list));
									node->next=headarray[count2+j][count1+k];
									node->candidate=notin[i][m];
									headarray[count2+j][count1+k]=node;
									see[count2+j][count1+k]=cancount;
									
								}
							}	


						}
						

					}
				}
			
			}
			count1=count1+size;
			if(count1==size*size)
			{
				count3++;
				count1=0;
				count2=count3*size;
			}
		


	}
}
void rule1()
{
	int prevcount=0;
	int i,j,k;
	int count1=0,count2=0,count5=0,m;
	int div1,div2;	
		// rule 2 implementation
		while(1)
		{
		
			prevcount=count;
			for(i=1;i<=size*size;i++)
			{
				for(j=1;j<=size*size;j++)
				{
					if(see[i][j]==1)
					{
						arr[i][j]=headarray[i][j]->candidate;
						free(headarray[i][j]);
						headarray[i][j]=NULL;
						//row update
						for(k=1;k<=size*size;k++)
						{
							count5=0;
							node1=headarray[i][k];
							while(node1)
							{
								count5++;
								if(node1->candidate==arr[i][j] && count5==1)
								{
							
									see[i][k]--;
									headarray[i][k]=node1->next;
									free(node1);
									break;
								}
								else if(node1->candidate==arr[i][j] && count5!=1)
								{
									see[i][k]--;
									node2->next=node1->next;
									free(node1);
									break;
								}
								else
								{
									node2=node1;
									node1=node1->next;
								}
							}
						}
						for(k=1;k<=size*size;k++)
						{
							count5=0;
							node1=headarray[k][j];
							while(node1)
							{
								count5++;
								if(node1->candidate==arr[i][j] && count5==1)
								{
							
									see[k][j]--;
									headarray[k][j]=node1->next;
									free(node1);
									break;
								}
								else if(node1->candidate==arr[i][j] && count5!=1)
								{
									see[k][j]--;
									node2->next=node1->next;
									free(node1);
									break;
								}
								else
								{
									node2=node1;
									node1=node1->next;
								}
							}
						}
						div1=(i-1)/size;
						div2=(j-1)/size;
						for(k=(size*div1)+1;k<=(size*(div1+1));k++)
						{
							for(m=(size*div2)+1;m<=(size*(div2+1));m++)
							{
								count5=0;
								node1=headarray[k][m];
								while(node1)
								{
									count5++;
									if(node1->candidate==arr[i][j] && count5==1)
									{
							
										see[k][m]--;
										headarray[k][m]=node1->next;
										free(node1);
										break;
									}
									else if(node1->candidate==arr[i][j] && count5!=1)
									{
										see[k][m]--;
										node2->next=node1->next;
										free(node1);
										break;
									}
									else
									{
										node2=node1;
										node1=node1->next;
									}
								}
							}
						}
				
						count--;
						see[i][j]=0;
						
						update(i,j,arr[i][j]);
					}
				}
			}
		if(count==prevcount)
			break;
		}
		
}
void rule2_box()
{
	int prevcount;
	int count1=0,count2=0,count3=0;
	int i,j,k,l,m;
	int candicount=0;
	while(1)
	{
		prevcount=count;
		count1=0,count2=0,count3=0;
		for(i=0;i<size*size;i++)
		{
			
			for(j=1;j<=size;j++)
			{
				for(k=1;k<=size;k++)
				{
					

					if(see[count2+j][count1+k]!=0)
					{
					
						node1=headarray[count2+j][count1+k];
						while(node1)
						{
							candicount=0;
							
							if(candicount==0)
							{
								for(l=1;l<=size;l++)
								{
									for(m=1;m<=size;m++)
									{
										if(see[count2+l][count1+m]==0 || (m+count1==count1+k && l+count2==count2+j))
continue;
										else
										{
											node2=headarray[count2+l][count1+m];
											while(node2)
											{
												if(node2->candidate==node1->candidate)
												{
											
													candicount++;
													break;
												}
												node2=node2->next;
											}
										}
										
									}
									
								
								}
							}
							if(candicount==0)
							{
								see[count2+j][count1+k]=1;
								candi=node1->candidate;
								headarray[count2+j][count1+k]->next=NULL;
								headarray[count2+j][count1+k]->candidate=candi;
								assign();
								break;
							
							}
							
							node1=node1->next;
							
							
						}

					}
					
				}
			}

		
			count1=count1+size;
			if(count1==size*size)
			{
				count3++;
				count1=0;
				count2=count3*size;
			}


		}
		if(prevcount==count)
		break;
	}
	
}
void rule2_row()
{
	int prevcount;
	int count1=0,count2=0,count3=0;
	int i,j,k,l,m;
	int candicount=0;
	while(1)
	{
			prevcount=count;
			for(j=1;j<=size*size;j++)
			{
				for(k=1;k<=size*size;k++)
				{
					

					if(see[j][k]!=0)
					{
					
						node1=headarray[j][k];
						while(node1)
						{
							candicount=0;
							for(l=1;l<=size*size;l++)
							{

								if((see[j][l]!=0) && (l!=k))
								{

									node2=headarray[j][l];
									while(node2)
									{
										if((node2->candidate)==(node1->candidate))
										{
											candicount++;
											break;
										}
										node2=node2->next;
									}
								}
								if(candicount>=1)
									break;
							}
							
							if(candicount==0)
							{
								
								
								see[j][k]=1;
								candi=node1->candidate;
								headarray[j][k]->next=NULL;
								headarray[j][k]->candidate=candi;
								assign();
								break;
							
							}
							
							else
							node1=node1->next;
							
							
						}

					}
					
				}
			}
	
		if(prevcount==count)
		break;
	}
}
void rule2_col()
{
	int prevcount;
	int count1=0,count2=0,count3=0;
	int i,j,k,l,m;
	int candicount=0;
	while(1)
	{
			prevcount=count;
			count1=0,count2=0,count3=0;
			
			for(j=1;j<=size*size;j++)
			{
				for(k=1;k<=size*size;k++)
				{
					

					if(see[k][j]!=0)
					{
					
						node1=headarray[k][j];
						while(node1)
						{
							candicount=0;
							for(l=1;l<=size*size;l++)
							{

								if((see[l][j]==0) || (l==k))
								continue;
								else
								{

									node2=headarray[l][j];
									while(node2)
									{
										if((node2->candidate)==(node1->candidate))
										{
											candicount++;
											break;
										}
										node2=node2->next;
									}
								}
								if(candicount>=1)
									break;
							}
							
							if(candicount==0)
							{
								
								see[k][j]=1;
								candi=node1->candidate;
								headarray[k][j]->next=NULL;
								headarray[k][j]->candidate=candi;
								assign();
								break;
							
							}
							else
							node1=node1->next;
							
							
						}

					}
					
				}
			}

			
		if(prevcount==count)
		break;
	}
}
void rule3()
{
	
	int prevcount;
	int i,j,k;
	int m,ab,bc,o,l;
	int count1=0,count2=0,count3=0;
	int arr1[3],arr2[3];
	int flag=0;
	int size1=2;
	int count5=0;
	int count10=0;
	int initial=0;
	while(1)
	{
	
		prevcount=count;
		for(i=1;i<=size*size;i++)
		{
			for(j=1;j<=size*size;j++)
			{
				if(see[i][j]==2)
				{
					arr1[0]=headarray[i][j]->candidate;
					arr1[1]=headarray[i][j]->next->candidate;
					for(k=j+1;k<=size*size;k++)
					{
					
					
						if(see[i][k]==2)
						{
						
							arr2[0]=headarray[i][k]->candidate;
							arr2[1]=headarray[i][k]->next->candidate;
							flag=compare(arr1,arr2,size1);
							if(flag==1)
							{
								
								for(m=0;m<=1;m++)
								{
									for(ab=1;ab<=size*size;ab++)
									{
										count5=0;
										if(ab==j || ab==k)
										continue;
										else
										{
											node1=headarray[i][ab];
											while(node1)
											{
												count5++;
												if(node1->candidate==arr1[m] && count5==1)
												{
												
													see[i][ab]--;
													headarray[i][ab]=node1->next;
													free(node1);
													break;
												}
												else if(node1->candidate==arr1[m] && count5!=1)
												{
													see[i][ab]--;
													node2->next=node1->next;
													free(node1);
													break;
												}
												else
												{
													node2=node1;
													node1=node1->next;
												}
											}
										}
									}
								}
							}
						

						}
						else
						continue;
					}
				}
			}
		}
	assign();
	
	if(prevcount==count)
	break;
	}
	
	 count1=0,count2=0,count3=0;
	 flag=0;
	 count5=0;
	 count10=0;
	 initial=0;
	//column pairs remove
	while(1)
	{
	
		prevcount=count;
		for(i=1;i<=size*size;i++)
		{
			for(j=1;j<=size*size;j++)
			{
				if(see[j][i]==2)
				{
					arr1[0]=headarray[j][i]->candidate;
					arr1[1]=headarray[j][i]->next->candidate;
					for(k=j+1;k<=size*size;k++)
					{
					
					
						if(see[k][i]==2)
						{
						
							arr2[0]=headarray[k][i]->candidate;
							arr2[1]=headarray[k][i]->next->candidate;
							flag=compare(arr1,arr2,size1);
							
							if(flag==1)
							{
								
								for(m=0;m<=1;m++)
								{
									for(ab=1;ab<=size*size;ab++)
									{
										count5=0;
										if(ab==j || ab==k)
										continue;
										else
										{
											node1=headarray[ab][i];
											while(node1)
											{
												count5++;
												if(node1->candidate==arr1[m] && count5==1)
												{
												
													see[ab][i]--;
													headarray[ab][i]=node1->next;
													free(node1);
													break;
												}
												else if(node1->candidate==arr1[m] && count5!=1)
												{
													see[ab][i]--;
													node2->next=node1->next;
													free(node1);
													break;
												}
												else
												{
													node2=node1;
													node1=node1->next;
												}
											}
										}
									}
								}
							}
						

						}
						else
						continue;
					}
				}
			}
		}
	assign();
	
	if(prevcount==count)
	break;
	}
	
	count1=0,count2=0,count3=0;
	 flag=0;
	 count5=0;
	 count10=0;
	 initial=0;
	

	// box pairs remove
	/*while(1)
	{
		
		prevcount=count;
		for(o=1;o<=size*size;o++)
		{
	
			
			for(i=1;i<=size;i++)
			{
				for(j=1;j<=size;j++)
				{
					if(see[count2+i][count1+j]==2)
					{
						
						
						count10=0;
						arr1[0]=headarray[count2+i][count1+j]->candidate;
						arr1[1]=headarray[count2+i][count1+j]->next->candidate;
						
						for(k=i;k<=size;k++)
						{
							if(count10==0)
								initial=j+1;
							else
								initial=1;
							for(l=initial,count10++;l<=size;l++)
							{
								
							
								if(see[count2+k][count1+l]==2)
								{
									
									arr2[0]=headarray[count2+k][count1+l]->candidate;
									arr2[1]=headarray[count2+k][count1+l]->next->candidate;
									flag=compare(arr1,arr2,size1);
									
									if(flag==1)
									{
									
										for(m=0;m<=1;m++)
										{
											for(ab=1;ab<=size;ab++)
											{
											for(bc=1;bc<=size;bc++)
											{
												count5=0;
												if(((count2+ab==count2+k) && (count1+bc==count1+l))||((count2+ab==count2+i)&&(count1+bc==count1+j)))
												continue;
												else
												{
													node1=headarray[count2+ab][count1+bc];
													while(node1)
													{
														count5++;
														if(node1->candidate==arr1[m] && count5==1)
														{
												
															see[count2+ab][count1+bc]--;
															headarray[count2+ab][count1+bc]=node1->next;
															//free(node1);
															break;
														}
														else if(node1->candidate==arr1[m] && count5!=1)
														{
															see[count2+ab][count1+bc]--;
															node2->next=node1->next;
															//free(node1);
															break;
														}
														/*else
														{
															node2=node1;
										 					node1=node1->next;															

														}
													}
												}
											}
											}
										}
									}
						

								}
								else
								continue;
							}
						
						}
					}
				}
				


			}
			count1=count1+size;
			if(count1==size*size)
			{
				count3++;
				count1=0;
				count2=count3*size;
			}

		}
	assign();
	
	if(prevcount==count)
	break;
	}*/
	//printf("boxpairs=%d\n",count);
}
void rule4()
{
	int prevcount;
	int i,j,k;
	int m,ab,bc,o,l;	
	int initial=0,initial2=0;
	int count1=0,count2=0,count3=0,count5=0;
	int arr1[3],arr2[3],arr3[3];
	int size2=3;
	int flag=0;
	int count10=0;
	int count11=0;
	int lk,lm;
	
	while(1)
	{
	
		prevcount=count;
		for(i=1;i<=size*size;i++)
		{
			for(j=1;j<=size*size;j++)
			{
				if(see[i][j]==3)
				{
					arr1[0]=headarray[i][j]->candidate;
					arr1[1]=headarray[i][j]->next->candidate;
					arr1[2]=headarray[i][j]->next->next->candidate;
					for(k=j+1;k<=size*size;k++)
					{
					
					
						if(see[i][k]==3)
						{
						
							arr2[0]=headarray[i][k]->candidate;
							arr2[1]=headarray[i][k]->next->candidate;
							arr2[2]=headarray[i][k]->next->next->candidate;
							flag=compare(arr1,arr2,size2);
							
							if(flag==1)
							{
								
								for(l=k+1;l<=size*size;l++)
								{
									if(see[i][l]==3)
									{
										arr3[0]=headarray[i][l]->candidate;
										arr3[1]=headarray[i][l]->next->candidate;
										arr3[2]=headarray[i][l]->next->next->candidate;
										flag=compare(arr1,arr3,size2);
										if(flag==1)
										{
										for(m=0;m<=2;m++)
										{
											for(ab=1;ab<=size*size;ab++)
											{
												count5=0;
												if(ab==j || ab==k || ab==l)
												continue;
												else
												{
													node1=headarray[i][ab];
													while(node1)
													{
														count5++;
														if(node1->candidate==arr1[m] && count5==1)
														{
												
															see[i][ab]--;
															headarray[i][ab]=node1->next;
															free(node1);
															break;
														}
														else if(node1->candidate==arr1[m] && count5!=1)
														{
															see[i][ab]--;
															node2->next=node1->next;
															free(node1);
															break;
														}
														else
														{
															node2=node1;
															node1=node1->next;
														}
													}
												}
											}
										}
										}
									}
								}
							}
						

						}
						else
						continue;
					}
				}
			}
		}
	assign();
	
	
	if(prevcount==count)
	break;
	}
	

// row triple
	
	 count1=0,count2=0,count3=0,count5=0;
	 flag=0;
	 count10=0;
	 count11=0;

	while(1)
	{
	
		prevcount=count;
		for(i=1;i<=size*size;i++)
		{
			for(j=1;j<=size*size;j++)
			{
				if(see[j][i]==3)
				{
					arr1[0]=headarray[j][i]->candidate;
					arr1[1]=headarray[j][i]->next->candidate;
					arr1[2]=headarray[j][i]->next->next->candidate;
					for(k=j+1;k<=size*size;k++)
					{
					
					
						if(see[k][i]==3)
						{
						
							arr2[0]=headarray[k][i]->candidate;
							arr2[1]=headarray[k][i]->next->candidate;
							arr2[2]=headarray[k][i]->next->next->candidate;
							flag=compare(arr1,arr2,size2);
							
							if(flag==1)
							{
								
								for(l=k+1;l<=size*size;l++)
								{
									if(see[l][i]==3)
									{
										arr3[0]=headarray[l][i]->candidate;
										arr3[1]=headarray[l][i]->next->candidate;
										arr3[2]=headarray[l][i]->next->next->candidate;
										flag=compare(arr1,arr3,size2);
										if(flag==1)
										{
										for(m=0;m<=2;m++)
										{
											for(ab=1;ab<=size*size;ab++)
											{
												count5=0;
												if(ab==j || ab==k || ab==l)
												continue;
												else
												{
													node1=headarray[ab][i];
													while(node1)
													{
														count5++;
														if(node1->candidate==arr1[m] && count5==1)
														{
												
															see[ab][i]--;
															headarray[ab][i]=node1->next;
															free(node1);
															break;
														}
														else if(node1->candidate==arr1[m] && count5!=1)
														{
															see[ab][i]--;
															node2->next=node1->next;
															free(node1);
															break;
														}
														else
														{
															node2=node1;
															node1=node1->next;
														}
													}
												}
											}
										}
										}
									}
								}
							}
						

						}
						else
						continue;
					}
				}
			}
		}
	assign();
	if(prevcount==count)
	break;
	}
	
	
	

	 count1=0,count2=0,count3=0,count5=0;
	 flag=0;
	 count10=0;
	 count11=0;
// box triple
	while(1)
	{
		
		prevcount=count;
		for(o=1;o<=size*size;o++)
		{
	
			
			for(i=1;i<=size;i++)
			{
				for(j=1;j<=size;j++)
				{
					if(see[count2+i][count1+j]==3)
					{
						
						
						count10=0;
						arr1[0]=headarray[count2+i][count1+j]->candidate;
						arr1[1]=headarray[count2+i][count1+j]->next->candidate;
						arr1[2]=headarray[count2+i][count1+j]->next->next->candidate;
						for(k=i;k<=size;k++)
						{
							if(count10==0)
								initial=j+1;
							else
								initial=1;
							for(l=initial,count10++;l<=size;l++)
							{
								
							
								if(see[count2+k][count1+l]==3)
								{
									count11=0;
									arr2[0]=headarray[count2+k][count1+l]->candidate;
									arr2[1]=headarray[count2+k][count1+l]->next->candidate;
									arr2[2]=headarray[count2+k][count1+l]->next->next->candidate;
									flag=compare(arr1,arr2,size2);
									
									if(flag==1)
									{
										for(lk=k;lk<=size;lk++)
										{
											flag=0;
											if(count11==0)
											initial2=l+1;
											else
											initial2=1;
											for(lm=initial2,count11++;lm<=size;lm++)
											{
												if(see[count2+lk][count1+lm]==3)
												{
												arr3[0]=headarray[count2+lk][count1+lm]->candidate;
												arr3[1]=headarray[count2+lk][count1+lm]->next->candidate;
												arr3[2]=headarray[count2+lk][count1+lm]->next->next->candidate;										
												flag=compare(arr1,arr3,size2);
												
												if(flag==1)
												{
													
									
													for(m=0;m<=2;m++)
													{
														for(ab=1;ab<=size;ab++)
														{
														for(bc=1;bc<=size;bc++)
														{
															count5=0;
															if(((count2+ab==count2+k) && (count1+bc==count1+l))||((count2+ab==count2+i)&&(count1+bc==count1+j))|| ((count2+ab==count2+lk)&&(count1+bc==count1+lm)))
															continue;
															else
															{
																node1=headarray[count2+ab][count1+bc];
																while(node1)
																{
																	count5++;
																	if(node1->candidate==arr1[m] && count5==1)
																	{
												
																		see[count2+ab][count1+bc]--;
																		headarray[count2+ab][count1+bc]=node1->next;
																		free(node1);
																		break;
																	}
																	else if(node1->candidate==arr1[m] && count5!=1)
																	{
																		see[count2+ab][count1+bc]--;
																		node2->next=node1->next;
																		free(node1);
																		break;
																	}
																	else
																	{
																		node2=node1;
																		node1=node1->next;
																	}
																}
															}
														}
														}
													}
												}
												}
											}
										}
									}
						

								}
								else
								continue;
							}
						
						}
					}
				}
				


			}
			count1=count1+size;
			if(count1==size*size)
			{
				count3++;
				count1=0;
				count2=count3*size;
			}

		}
	assign();
	
	if(prevcount==count)
	break;
	}
}

