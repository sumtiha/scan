#include <vector> //vec
#include <iostream> //cout
#include <fstream> //file input
#include <sstream> //stringstream
#include <cstdlib> //atof
#include  <algorithm> //sort
using namespace std;
typedef std::vector<int> intvec;
typedef std::vector<float> floatvec;
// Desinger Sumitha George test change
//to collect data from file and separate to a bitmapper 
struct BoundingBox
{
  float lowerboundx1;
  float lowerboundx2;
  float upperboundy1;
  float upperboundy2; 

};
struct BitmapBBox
{
  float lowerboundx1;
  float lowerboundx2;
  float height;
  float width;
  int fill;

};
int main ()

{
vector<BoundingBox> bb;
vector<BoundingBox> bb_hr;
vector<BitmapBBox> bitmap;
BoundingBox bb1;
BitmapBBox bitmap_temp;
//initialize bitmap_temp with null;
bitmap_temp.lowerboundx1=0; bitmap_temp.lowerboundx2=0; bitmap_temp.height=0;bitmap_temp.width=0;bitmap_temp.fill=0;

floatvec ll1;
floatvec ll2;
floatvec uu1;
floatvec uu2;

//read from file
string line ;
string field;
//stringstream ss( line );
std::ifstream myfile("bitmap_input.txt");

	for (;getline(myfile,line);)
      {      cout <<line<<endl;
             stringstream ss( line );
    //take the first numbers separated by full colon
             getline(ss,field,':');
                    bb1.lowerboundx1=(float)atof(field.c_str());
             getline(ss,field,':');
                    bb1.upperboundy1=(float)atof(field.c_str());	
             getline(ss,field,':');
                    bb1.lowerboundx2=(float)atof(field.c_str());	
             getline(ss,field,':');
                    bb1.upperboundy2=(float)atof(field.c_str());
                     bb.push_back(bb1);	
             cout <<endl;

      }
//display inputs and transfring the corrdinates to ll1,uu1,etc
   vector<BoundingBox>::iterator it=bb.begin();
   for(;it !=bb.end();it++)
      { 
    //   cout  <<(*it).lowerboundx1<< " " <<(*it).lowerboundx2<<" " <<  (*it).upperboundy1 <<" "<< (*it).upperboundy2 ;
       uu1.push_back((*it).upperboundy1);
       uu2.push_back((*it).upperboundy2); 
      } 
//sort the matric
      std::sort (uu1.begin(),uu1.end());
      std::sort (uu2.begin(),uu2.end());
//display after  sorted can be removed    
    /*
      cout << "uu221.md1"<<endl;
    vector<float>::iterator it4=uu1.begin();
    for(;it4 !=uu1.end();it4++)
      { cout  <<(*it4);
       cout <<endl;
      }
      */
//get the first height  //make it effeicnt //remove double whiles 
      float hgt=0;float wdt=0;
      float abs_hgt_up=0;
      float abs_hgt_lo=0;
      float abs_wdt_up=0;
      float abs_wdt_lo=0;
      int fill=0;
       while (!uu1.empty()|| !uu2.empty())
       {     abs_hgt_lo=abs_hgt_up;
           if (!uu1.empty()&& !uu2.empty())
                {
                  if (uu1.front()<uu2.front())
                     { hgt=uu1.front()- abs_hgt_up;
                       abs_hgt_up=uu1.front();
                       uu1.erase(uu1.begin());
                      cout <<"height" <<hgt<<endl;
                     }
                  else if ( uu1.front()>uu2.front())
                     { hgt=uu2.front()-abs_hgt_up;
                      abs_hgt_up=uu2.front();
                       uu2.erase(uu2.begin());
                       cout <<"height" <<hgt<<endl;
                     }
                  else 
                    {hgt=uu1.front()-abs_hgt_up;
                       abs_hgt_up=uu1.front();
                      uu1.erase(uu1.begin());
                      uu2.erase(uu2.begin());
                      cout <<"height" <<hgt<<endl;
                    } 
               } 
           else if (!uu1.empty()&& uu2.empty())
                     { hgt=uu1.front()- abs_hgt_up;
                      abs_hgt_up=uu1.front();
                     uu1.erase(uu1.begin());
                     cout <<"height" <<hgt<<endl;
                     }
           else  
                     {
                      hgt=uu2.front()-abs_hgt_up;
                      abs_hgt_up=uu2.front();
                       uu2.erase(uu2.begin());
                       cout <<"height" <<hgt<<endl;
                     }
           cout <<"horontal loop "<<endl;
           //pick the polygons in the selected area btween abs_hgt_lo and abs_hgt_up if there any //algo can be make efiecint by cutting and slicing
           //to add later
           if (hgt!=0)
               {  //
                for(unsigned k=0;k<bb.size();k++)
                    {
                      if( bb[k].upperboundy1<=abs_hgt_lo &&  bb[k].upperboundy2>=abs_hgt_up)
                          {
                          // cout<<"it " <<k<< "lowerbox"<<bb[k].lowerboundx1<<endl;
                           bb_hr.push_back(bb[k]);
                          }
                    } 
                //now bb_hr has the elements in horizontal 
                ////display inputs and transfring the corrdinates to ll1,uu1,etc
                   ll1.clear();
                   ll2.clear();

                 vector<BoundingBox>::iterator it5=bb_hr.begin();
                for(;it5 !=bb_hr.end();it5++)
                    { 
                     ll1.push_back((*it5).lowerboundx1);
                     ll2.push_back((*it5).lowerboundx2);
                     } 
                 std::sort (ll1.begin(),ll1.end());
                 std::sort (ll2.begin(),ll2.end());

                 //making the boxes  
               float abs_wdt_up=0;
               float abs_wdt_lo=0;
               while (!ll1.empty()|| !ll2.empty())
                    { abs_wdt_lo=abs_wdt_up;
               if (!ll1.empty()&& !ll2.empty())
                    {
                      if (ll1.front()<ll2.front())
                         { wdt=ll1.front()- abs_wdt_up;
                           abs_wdt_up=ll1.front();
                           ll1.erase(ll1.begin());
                          cout <<"width1 " <<wdt<<endl;
                         }
                      else if ( ll1.front()>ll2.front())
                         { wdt=ll2.front()-abs_wdt_up;
                          abs_wdt_up=ll2.front();
                           ll2.erase(ll2.begin());
                           cout <<"width2 " <<wdt<<endl;
                         }
                      else 
                        {wdt=ll1.front()-abs_wdt_up;
                           abs_wdt_up=ll1.front();
                          ll1.erase(ll1.begin());
                          ll2.erase(ll2.begin());
                          cout <<"width3 " <<wdt<<endl;
                        } 
                   } 
               else if (!ll1.empty()&& ll2.empty())
                         { wdt=ll1.front()- abs_wdt_up;
                          abs_wdt_up=ll1.front();
                         ll1.erase(ll1.begin());
                         cout <<"width4 " <<wdt<<endl;
                         }
               else  
                         {
                          wdt=ll2.front()-abs_wdt_up;
                          abs_wdt_up=ll2.front();
                           ll2.erase(ll2.begin());
                           cout <<"width5 " <<wdt<<endl;
                         }
                  }
             bb_hr.clear();
             }  
        }

             //remove all elemnts from bb_hr
            
              
        
       // cout<<"vecot front" <<uu1.front()<<endl;
        //cout<<"vecot front" <<uu1.front()<<endl;
         

  
return 0;
}

