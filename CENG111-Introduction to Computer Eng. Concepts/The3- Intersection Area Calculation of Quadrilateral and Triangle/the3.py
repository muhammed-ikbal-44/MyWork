import math
def area(Q, T):

    dortgen=Q
    ucgen=T
   
    #eğim formülü ile kesişim bulma 
    #Burada yapılan, girilen 2 line'nın kesişim noktasını hesaplamaktır
    def kesisim(line1,line2):
        
        interx=1.0
        intery=1.0
        
        if (line1[1][0]!=line1[0][0]) and (line2[1][0]!=line2[0][0]):    
            if (line1[1][1]-line1[0][1])/(line1[1][0]-line1[0][0])!=(line2[1][1]-line2[0][1])/(line2[1][0]-line2[0][0]):
            
                if abs(line1[0][0]-line1[1][0])<0.0000001 and (line2[0][0]!=line2[1][0]):
                    interx=line1[0][0]
                    m2=(line2[1][1]-line2[0][1])/(line2[1][0]-line2[0][0])
                    intery=m2*(interx-line2[0][0])+line2[0][1]
                elif (line1[0][0]!=line1[1][0]) and abs(line2[0][0]-line2[1][0])<0.0000001:
                    interx=line2[0][0]
                    m1=(line1[1][1]-line1[0][1])/(line1[1][0]-line1[0][0])
                    intery=m1*(interx-line1[0][0])+line1[0][1]
                
                else:
                    m1=(line1[1][1]-line1[0][1])/(line1[1][0]-line1[0][0])
                    m2=(line2[1][1]-line2[0][1])/(line2[1][0]-line2[0][0])
                    interx=((m1*line1[0][0])-(m2*line2[0][0])-line1[0][1]+line2[0][1])/(m1-m2)
                    intery=m1*(interx-line1[0][0])+line1[0][1]
        elif (line1[1][0]!=line1[0][0]) and abs((line2[1][0]-line2[0][0]))<0.0000001:
            interx=line2[0][0]
            m1=(line1[1][1]-line1[0][1])/(line1[1][0]-line1[0][0])
            intery=m1*(interx-line1[0][0])+line1[0][1]
            
        elif abs((line1[1][0]-line1[0][0]))<0.0000001 and (line2[1][0]!=line2[0][0]):
            interx=line1[0][0]
            m2=(line2[1][1]-line2[0][1])/(line2[1][0]-line2[0][0])
            intery=m2*(interx-line2[0][0])+line2[0][1]
            

        
        
        interseciton=[interx,intery]  
        
        return interseciton


    #Üçgen ve Dörtgenin kenarlarını değerlere atadım, lakin kullanışsız gibi duruyor.
    

    #Şekillerin köşe noktalarını  listeye manuel ekledim
    kesisimliste=dortgen+ucgen


    #iç içe 2 fonksyon ile tüm keşisimleri buldum.(dötrgene ait 4 doğru için "i", üçgen için "a" değeri)
    for i in range(0,4):
        for a in range(0,3):
            deger=tuple(kesisim((dortgen[i],dortgen[i-1]),(ucgen[a],ucgen[a-1])))
            kesisimliste.append(deger)
            
            


    #Cosinüs Teoremi ile noktaların açılarını buldum, eğer cisim içerde ise açılar
    #toplamı 360 derece olmak zorundadır.(istisnalar var ama hem dörtgen hem üçgen için sağlayan bir değer olmaması gerekiyor.)
    def acibul(p1,p2,p3):  #istenen açı p3'ün karşısında olmak zorunda  ona göre
        
        uzun1=(((p2[0]-p1[0])**2)+((p2[1]-p1[1])**2))**(1/2)
        
        uzun2=(((p2[0]-p3[0])**2)+((p2[1]-p3[1])**2))**(1/2)
        uzun3=(((p3[0]-p1[0])**2)+((p3[1]-p1[1])**2))**(1/2)
   
        if abs(uzun2+uzun3-uzun1)<0.0000001:
            boolean=True    #Eğer keşisim noktası kenarlar üzerinde ise kenarlara olan uzunluklar toplamı iki kenar arası uzaklığa eşit olur. listeye eklenbilir
            return boolean
            
        else:
            arg = ((uzun1 ** 2) - (uzun3 ** 2) - (uzun2 ** 2)) / (-2 * uzun2 * uzun3)
            arg = max(-1, min(1, arg))   #Bir çok kez domain error aldım, sebebi de cosinüsün sınırlarnı belirtmemek. bu yapı bu yüzden yazıldı.
        
            aci=math.acos(arg)
            degree=aci*(360/(2*math.pi))  #sayısal açı değerini radyana çevirme
        
            return degree

    aciListe=[]
    intersectionListe=[]
    tmp=[]
    for j in range(0,len(kesisimliste)):
        a=0
    
        for i in range(0,4):
            if acibul(dortgen[i],dortgen[i-1],kesisimliste[j]) is True: 
                intersectionListe.append(kesisimliste[j])
            else:
                a+=acibul(dortgen[i],dortgen[i-1],kesisimliste[j])
                
                aciListe.append(a)
                if abs(a-360)<0.00000001:
                    intersectionListe.append(kesisimliste[j])
            if len(aciListe) == 4:
                    tmp.append(sum(aciListe))
                    aciListe.clear()
    dortgenkesisim=list(set(intersectionListe))

    intersectionListe2=[]   
    temp2=[]
    for j in range(0,len(kesisimliste)):
        a=0
        for i in range(0,3):
            if acibul(ucgen[i],ucgen[i-1],kesisimliste[j]) is True: 
                intersectionListe2.append(kesisimliste[j])
            else:
                a+=acibul(ucgen[i],ucgen[i-1],kesisimliste[j])
                
                aciListe.append(a)
                if abs(a-360)<0.00000001:
                    intersectionListe2.append(kesisimliste[j])
            if len(aciListe) == 4:
                    temp2.append(sum(aciListe))
                    aciListe.clear()      
    ucgenkesisim=list(set(intersectionListe2))

    def ortak(list1, list2): # iki listede ortak olan elemanlar ortak kesişim alanında demektir.
        result = []
        for nokta in list1:
            if nokta in list2:
                result.append(nokta)
        return result

    intersectionarea=ortak(dortgenkesisim,ucgenkesisim)
    


    """19.12.2023/Salı
    kullanacağım sıralama için belirli birkaç belirli yöntem var 1)açılardan gidebilirim her seferinde mutlak açı değerinin en küçük olduğu noktaya giderim  
    2)Graham-Scan'ın convex Hull metodunu kullanabilirim yeterli araştırma yapım ve kendi koduma entegre edebilirim, 3) en güvensiz olanı ama graham
    scanı anlayamazsan ve eğimi yapamazsam son çare, listedeki elemanların keninden bi sonraki elemanla yaptığı açıların toplamı o çokgenin iç açıları toplamı olana kadar
    listedeki sıralamayı değişirim ama bu 5gen için 120 işlem, 6gen için daha da fazla işlem olur ve çok sağlıksız olur."""
    def custom_reduce(function, iterable, initializer=None):
        it = iter(iterable)
        if initializer is None:
            try:                    #Graham_scanda reduce fonksyonu kullanılyor(bir kütüphaneden) tabi math harici yasak olduğu için içeriğini bulup uyarladım
                initializer = next(it)
            except StopIteration:
                raise TypeError("custom_reduce() of empty sequence with no initial value")
        accumulator = initializer
        for element in it:
            accumulator = function(accumulator, element)
        return accumulator



    def convex_hull_graham(points):
        
        
        TURN_LEFT = (1)

        def cmp(a, b):
            return (a > b) - (a < b)

        def turn(p, q, r):
            return cmp((q[0] - p[0])*(r[1] - p[1]) - (r[0] - p[0])*(q[1] - p[1]), 0)

        def _keep_left(hull, r):
            while len(hull) > 1 and turn(hull[-2], hull[-1], r) != TURN_LEFT:
                hull.pop()
            if not len(hull) or hull[-1] != r:
                hull.append(r)
            return hull

        points = sorted(points)
        l = custom_reduce(_keep_left, points, [])
        u = custom_reduce(_keep_left, reversed(points), [])
        return l.extend(u[i] for i in range(1, len(u)-1)) or l

    def areafind(listofinter):
        carpim1=[]
        carpim2=[]
        for i in range(0,len(listofinter)):
            carpim1.append(listofinter[i][0]*listofinter[i-1][1])
            carpim2.append(listofinter[i][1]*listofinter[i-1][0])
            
        alan=0.5*(abs(sum(carpim1)-sum(carpim2)))
        return alan
            

    sorted_points=convex_hull_graham(intersectionarea)
    return areafind(sorted_points)
    

print(area([(6, 1), (13, 8), (14, 14), (12, 14)], [(3, 4), (10, 1),(4, 4)]))
   


   












































# ROUNDLARI KESİNLİKLE SİL




    

