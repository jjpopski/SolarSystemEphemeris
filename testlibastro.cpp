#include <iostream>
#include <cstring>
#include "astro.h"
#include "preferences.h"
#include <string>


static void reportPosition (Now *np, Obj *op);



class Site: public  Now {

public:  
      
    Site(double mj, double lon, double lt, double height);
    void stampa(void);
    double getMjd();
    
    
private:
       double m_lon,m_lat,m_height;
       std::string name;
    
};

class Planet   {

public:
      
      Planet(PLCode code);
      ~Planet(){ delete obj;}
      double ra,dec,range,az,el;

      void compute (Site* site);
      Planet() {};
      Obj* getObject();
      
      private:
      
    
    
protected:
        
            Obj* obj;
    
    
    
};


Planet::Planet(PLCode code)
{
    obj=new Obj();
    
    std::cout << "Code: " << code << std::endl;
    
    obj->any.co_type=PLANET;
    strcpy(obj->any.co_name,"Jupyter");
    obj->pl.plo_code=code;

    pref_set(PREF_EQUATORIAL,PREF_GEO);

    
    
}



void  Planet::compute(Site* site){
        std::cout << "Compute " <<std::endl;
    obj_cir (site, obj);

    ra=obj->any.co_ra;
    dec=obj->any.co_dec;
    az=obj->any.co_az;
    el=obj->any.co_alt;
    
}


Obj* Planet::getObject()
{
    return  obj;
    
    
}


class Jupiter : public Planet {

public:
    
     Jupiter() ;
    
    
    
};

Jupiter::Jupiter()
{

    std::cout << (int)this->obj->any.co_type <<"type" <<std::endl;
    
}



Site::Site(double mj, double lon, double lt, double height)
{
    this->n_mjd=mj-15020; // xephem uses mjd 0 as 1899 12 31 at 12:00
    this->n_lat=lt;
    this->n_lng=lon;
    this->n_epoch=J2000;
//     this->n_heigt=height;
    
}

void Site::stampa(void){

    std::cout<< "mjd:"<< this->n_mjd <<std::endl;
    std::cout << "lon:"<< raddeg(this->n_lng) << std::endl;
    std::cout << "lat:"<< raddeg(this->n_lat) << std::endl;
    
    
}

double Site::getMjd()
{

    return this->n_mjd+15020;
    
}









int main(int argc, char** argv){
    
   // Now now,*site=&now ;		
    /* Now and handy pointer */
    Site *site = new Site(59319.5,degrad(9.5),degrad(39.5),600);
	Obj obj,*op=&obj ;			/* Obj and handy pointer */
	
	Planet p =   Planet(JUPITER);
    Planet* sat = new Planet(SATURN);
    std::cout << "New Planet done" << std::endl;
    
//     
    site->stampa();
    
    
   //  memset (site, 0, sizeof(*site));		/* zero everything initially */
 //    cal_mjd (4, 15, 2021, &site->n_mjd);
     std::cout << site->n_mjd<<std::endl;
  //   site->n_lat= degrad(39.5);
  //   site->n_lng= degrad(9.0);
  //   site->n_tz=-2;
  //   site->n_temp=10;

//   pref_set(PREF_EQUATORIAL,PREF_TOPO);
    
     
// 	op->o_type = PLANET;			/* core type */
//op->pl_code = SUN;			/* ID code if PLANET */
 	//op->f_epoch = J2000;
 //	(void) strcpy (op->o_name, "Jupiter");	/* name */
// 	(void) obj_cir (site, op);		/* compute position @ now */

    p.compute(site);
   // sat->compute(site);
    
    std::cout << raddeg(p.ra) << " Radians" <<std::endl;

    
 	reportPosition (site, p.getObject());		/* print */
 //   reportPosition (site, sat->getObject());		/* print */
   
     
    
//    planpos(59319.5,JUPITER, 0, coord);
    
 //   std::cout << coord[0] << " " << coord[1] << " " << coord[2] << std::endl;
    
    return 0;
    
}
// 2459319.500000000     
static void
reportPosition (Now *np, Obj *op)
{
	int mon, year;
	double day;
	char sexa[32];

	printf ("Circumstances:\n");
	mjd_cal (np->n_mjd, &mon, &day, &year);
	printf ("UTC:       %d/%g/%d\n", mon, day, year);
	fs_sexa (sexa, raddeg(lat), 3, 3600);
	printf ("Latitude:  %s D:M:S +N\n", sexa);
	fs_sexa (sexa, raddeg(lng), 3, 3600);
	printf ("Longitude: %s D:M:S +E\n", sexa);
	printf ("\n");

	printf ("%s:\n", op->o_name);
	fs_sexa (sexa, radhr(op->s_ra), 3, 3600);
	printf ("RA:        %s H:M:S\n", sexa);
	fs_sexa (sexa, raddeg(op->s_dec), 3, 3600);
	printf ("Dec:       %s D:M:S\n", sexa);
	fs_sexa (sexa, raddeg(op->s_alt), 3, 3600);
	printf ("RA:        %f deg\n", raddeg(op->s_ra));
	printf ("Dec:       %f deg\n",  raddeg(op->s_dec));

    
    printf ("Altitude:  %s D:M:S\n", sexa);
	fs_sexa (sexa, raddeg(op->s_az), 3, 3600);
	printf ("Azimuth:   %s D:M:S\n", sexa);
	printf ("\n");

	printf ("\n");
}
