def check_month(month_calender):
    
    #Global Lists in order to calculate cost and chech the rules
    total_cost=[]
    checkList=[]

    #Rule1 mother (m): She works 4 days a week. But the off-day has to be fixed all over the month
    mlist=[x for x in range(0, len(month_calender)) if month_calender[x]=="m"]
    kalanList = [mlist[x]%5 for x in range(0,len(mlist))]
    birlesikList = [kalanList[i] for i in range(0,len(kalanList)) if kalanList[i]!=kalanList[i-1]]
    if birlesikList==[]:
        
        total_cost.append(len(mlist)*10)   
        
    else:
        checkList.append(1)
        
        
    #Rule2  father (f): Works on all workdays of the week. Can take two workdays off per month. These days cannot be consecutive. 
    flist=[i for i in range (0,len(month_calender)) if month_calender[i]=="f"]
    if len(flist)<=2 and len(flist)>0:
        if abs(flist[0]-flist[-1])==1:
            if flist==[4,5] or flist==[9,10] or flist==[14,15] or flist==[19,20]:
                total_cost.append(len(flist)*20)
            else:
                checkList.append(2)
        else:
            total_cost.append(len(flist)*20) 
    elif len(flist)==0:
        total_cost.append(len(flist)*20)       
    else:
        checkList.append(2)      
    

    #Rule3 babysitter (b):She is always available. However, if she is booked on two consecutive days that are less than 3 days (whether or not they are weekdays or weekend days) apart
    #(e.g., Monday and Tuesday are 0-day apart whereas Friday and the following Monday are two days apart), she will also charge for the intervening days, even though she won’t be
    #babysitting on those days.
    month_calender2=month_calender[:]
    month_calender2.insert(5,'x')
    month_calender2.insert(6,'x')
    month_calender2.insert(12,'x')
    month_calender2.insert(13,'x')
    month_calender2.insert(19,'x')
    month_calender2.insert(20,'x')
    month_calender2.insert(26,'x')
    month_calender2.insert(27,'x')

    blist=[i for i in range (0,len(month_calender2)) if month_calender2[i]=='b']
    bfarkList=[(blist[a]-blist[a-1]-1) for a in range(0,len(blist)) if blist[a]-blist[a-1]-1<3 and blist[a]-blist[a-1]-1>0 ]
    
    if bfarkList==[]:
        total_cost.append(len(blist)*30)
    
    else:    
        total_cost.append((sum(bfarkList)+len(blist))*30)


    #Rule4 4 grandma (g): Is usually available. She plays cards every Wednesday. Her card-play group has a strict rule that any group member can miss only one meeting per month


    glist=[g for g in range(0,len(month_calender)) if month_calender[g]=='g']
    kalanList2=[i for i in range(0,len(glist)) if glist[i]%5==2]

    if len(kalanList2)>1:
        checkList.append(4)
        


    else:
        total_cost.append(len(glist)*50)
        




        
    #Rule5  aunt (a1): Only available on Tuesdays and Fridays       
    a1list=[a1 for a1 in range(0,len(month_calender)) if month_calender[a1]=='a1']
    kalanList3=[a1list[i]%5 for i in range (0,len(a1list)) if a1list[i]%5==0 or a1list[i]%5==2 or a1list[i]%5==3 ]
    if len(kalanList3)>0:
        checkList.append(5)
    else:
        total_cost.append(len(a1list)*32)    
    

    #Rule6
    a2list=[a2 for a2 in range(0,len(month_calender)) if month_calender[a2]=='a2']
    
    liste=[x for x in range(1,len(month_calender2)) if month_calender2[x-1]=='a1' and month_calender2[x]=='a2']
    
    if len(liste):
        checkList.append(6)
    else:
        sum1=len(a2list)*27
        total_cost.append(sum1)    









    #Rule7 neighbour lady (n): Available on Monday, Tuesday and Wednesday
    nlist=[n for n in range(0,len(month_calender)) if month_calender[n]=="n"]
    kalanList4=[nlist[i] for i in range(0,len(nlist)) if nlist[i]%5==3 or nlist[i]%5==4]

    if kalanList4!=[]:
        checkList.append(7)
    else:
        if len(nlist)==1:
            total_cost.append(0)
        elif len(nlist)>1:
            sum2=(5**(len(nlist))-1)/4-1
            total_cost.append(sum2)
        else:
            total_cost.append(0)    

        
    
    #Last Part
    
        
        

    
    
    if checkList!=[]:
        return checkList
    else:
        
        return int(sum(total_cost))
    
    
#m1="n a1 n f a1 n a1 f a2 g a2 m n a2 a2 n n n b b a2".split()
#m3="f f g b a1 b n n a2 a2 b b n b a2 m a2 a2 a2 a2 b".split()
#print(check_month(m1))
#print(check_month(m3))






















                    


        



           
    


            
        

           
            
            


          


    








    





