#include "Hospital.h"

#include <cassert>

std::ostream& operator<<(std::ostream& s, const EventResult& r)
{
    int enumIndex = (r.type < 0 || r.type > InvalidEvent) ? InvalidEvent : r.type;
    s << "Time[" << r.timePoint << "]: ";
    switch (enumIndex)
    {
    case DoctorQueueCheck:
        s << "Doctor(" << r.patientIdOrDoctorIndex
            << ") checked the patient queue." << std::endl;
        break;
    case RegistrationQueueEntrance:
        s << "Patient(" << r.patientIdOrDoctorIndex
            << ") " << "is registering." << std::endl;
        break;
    case RegistrationEnd:
        s << "Patient(" << r.patientIdOrDoctorIndex
            << ") registeration is complete." << std::endl;
        break;
    case ExaminationEnd:
        s << "Patient(" << r.patientIdOrDoctorIndex
            << ") examination is completed." << std::endl;
        break;
    case InvalidEvent:
    default:
        s << "Invalid Event!" << std::endl;
        break;
    }

    return s;
}

int Doctor::ExamTimeOf(const Patient& patient) const
{
    int t= baselineExaminationTime;
    return ((MAX_PATIENT_PRIORTIY - patient.getPriority() + 1) * t);
    // TODO: Implement
}


Hospital::Hospital(const Doctor& d0,
    const Doctor& d1,
    int rTime, int docTime)
    : currentTime(0)
    , registrationTime(rTime)
    , doctorCheckTime(docTime)
{
    doctors[0] = d0;
    doctors[1] = d1;
    patientsInExam[0] = NULL;
    patientsInExam[1] = NULL;

    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 0));
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 1));
}

Hospital::~Hospital() {

    while (!regQueue.IsEmpty()) {
        Patient* patient = regQueue.Dequeue();
    }
}

void Hospital::AddPatient(int id, int priority)
{
    if(priority<0){
        return;
    }
    if (priority <= MAX_PATIENT_PRIORTIY) {
        Patient* npati =new Patient(id, priority);

        Event* registrationEvent=new Event(currentTime, RegistrationQueueEntrance,npati);
        eventQueue.InsertItem(registrationEvent);
        regQueue.Enqueue(npati);
    }
}

EventResult Hospital::DoSingleEventIteration()
{
    Event *currevent= eventQueue.RemoveFirstItem();
    if (currevent!=NULL) { //eger olay yoksa direk cik varsa ife fir
        
    
    

       
        EventResult result;                                     //ekelenek işlemleri resulta doldurduk
        currentTime= currevent->getTimePoint();
        result.type=currevent->getType();
        result.timePoint= currentTime;
    
    
    //******************************************************************************************//
    //*****************  İLK EVENT  ************************************************************//
        if(result.type== RegistrationQueueEntrance){  //type enum 1
    
            const Patient* pati=currevent->getPatient();
    
            result.patientIdOrDoctorIndex =currevent->getPatient()->getId();       //her seferinde ayni esitleme yapiacal
                                                                                    //sadece timeler farklı
            eventQueue.InsertItem(new Event(currentTime + registrationTime, RegistrationEnd,pati));
 //******************************************************************************************//
 //*****************  İKİNCİ EVENT  *********************************************************//
        }else if(result.type == RegistrationEnd){  //type enum 2
    
            result.patientIdOrDoctorIndex = currevent->getPatient()->getId();
            Patient* pat = regQueue.Dequeue();
    
    
            if(pat!=NULL){
                examQueue.InsertItemPrior(pat);
            }
    
        }
//******************************************************************************************//
//*****************  ÜÇÜNCÜ EVENT  *********************************************************//
        else if(result.type== DoctorQueueCheck){ //type enum 3
    
    
            result.patientIdOrDoctorIndex= currevent->getDoctorIndex();
    
            if(!examQueue.IsEmpty() && !patientsInExam[currevent->getDoctorIndex()]) {
                Patient* nextpat;
                nextpat = examQueue.RemoveFirstItem();
                
                patientsInExam[currevent->getDoctorIndex()] = nextpat;
                int time= doctors[currevent->getDoctorIndex()].ExamTimeOf(*nextpat) + currentTime;
                eventQueue.InsertItem(new Event(time, ExaminationEnd, nextpat)); //yeteer sayfaya sigmiyor
                
            }else if (!patientsInExam[currevent->getDoctorIndex()]) {
                    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, currevent->getDoctorIndex()));
            }
        }
//******************************************************************************************//
//*****************  DÖRDÜNCÜ EVENT  *******************************************************//
        else if (result.type == ExaminationEnd) {   //type enum 4
    
            const Patient* newp = currevent->getPatient();
            result.patientIdOrDoctorIndex = currevent->getPatient()->getId();
            
            int indx = -1; //flag
            
            
            if(patientsInExam[0]==newp){    //doktor muayene kontrol
                indx=0;
            } else if(patientsInExam[1]==newp){
                indx=1;
            }
           
    
            
            if (indx!=-1) {
                delete patientsInExam[indx];    //deletations
                patientsInExam[indx]= NULL;
    
                if (!examQueue.IsEmpty()) {
                    Patient* new_patient = examQueue.RemoveFirstItem();
                    patientsInExam[indx] = new_patient;
                    int time=currentTime + doctors[indx].ExamTimeOf(*new_patient);
                    eventQueue.InsertItem(new Event(time, ExaminationEnd, new_patient));
                    
                }
                else {
                    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, indx));
                }
    
    
    
            }
        }
    
        else {
            //  InvalidEvent'te ne yapacağız pdf de hiçbişey yazmıypr
            result.type=InvalidEvent;
            
        }
    
        
        delete currevent;
    
        return result;
    }  else { //eğer en bastaki ife girmeydiyse olay yok, direk delete+return.
        
        return EventResult();
    }
    // TODO: Implement
    //return EventResult();
}