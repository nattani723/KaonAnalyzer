#ifndef _EventType_h_
#define _EventType_h_

#include "Event.h"

namespace EventType {

const std::vector<std::string> Types = { "Signal","OtherHYP","OtherNu","EXT","Dirt","All","Data" };
const std::vector<std::string> Captions = {"Signal","Other HYP","Other #nu","Dirt","EXT","Data"};
const std::vector<int> Colors = {8,46,38,30,15,0};

//const std::vector<std::string> Types2 = {"DirectLambda","RESLambda","DISLambda","DirectHYP","RESHYP","DISHYP","Neutron","Other","Dirt","EXT","Data","All"};
const std::vector<std::string> Types2 = {"DirectLambda","DirectHYP","Neutron","Dirt","RESLambda","RESHYP","Other","EXT","DISLambda","DISHYP","Data"};
const std::vector<std::string> Captions2 = {"Direct #Lambda","Direct Hyp","Neutron","Dirt","RES #Lambda","RES Hyp","Other #nu","EXT","DIS #Lambda","DIS Hyp","Data"};
const std::vector<int> Colors2 = {8,kBlue-7,kRed-7,kCyan+3,kGreen+3,kBlue-10,kRed-10,kMagenta-7,30,15,0};

const std::vector<std::string> Procs = {"Signal","OtherHYP","EXT","Dirt","CCQEL","CCRES","CCDIS","CCMEC","CCCOH","NC","Other","Data"};
const std::vector<std::string> Captions3 = {"Signal","Other HYP","EXT","Dirt","CCQEL","CCRES","CCDIS","CCMEC","CCCOH","NC","Other","Data"};
const std::vector<int> Colors3 = {8,46,2,3,4,5,6,7,9,11,12,30,15,0};

///////////////////////////////////////////////////////////////////////////////////////////////

// Get the event category 

std::string GetType(Event e){

   if(!e.Mode.size()) throw std::invalid_argument("GetType: Event has Mode.size() = 0, should be at least 1");

   if(e.Mode.at(0) == "Data") return "Data";
   else if(e.Mode.at(0) == "EXT") return "EXT";
   else if(e.Mode.at(0) == "Dirt") return "Dirt";
   else if(e.EventIsSignal) return "Signal";
   else if(e.Mode.at(0) == "HYP") return "OtherHYP";

   return "OtherNu";
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Get the event category using different labelling convention

std::string GetType2(Event e){

   if(!e.Mode.size()) throw std::invalid_argument("GetType2: Event has Mode.size() = 0, should be at least 1");

   std::string type;

   if(e.Mode.at(0) == "Data") return "Data";
   else if(e.Mode.at(0) == "EXT") return "EXT";
   else if(e.Mode.at(0) == "Dirt") return "Dirt";

   bool islambdacharged =  std::find(e.IsLambdaCharged.begin(),e.IsLambdaCharged.end(), true) != e.IsLambdaCharged.end();

   if(e.EventIsSignal) return "DirectLambda";
   else if(e.Mode.at(0) == "HYP") return "DirectHYP"; 
   else if(e.Mode.at(0) == "RES" && islambdacharged) return "RESLambda";
   else if(e.Mode.at(0) == "RES" && e.Hyperon.size()) return "RESHYP"; 
   else if(e.Mode.at(0) == "DIS" && islambdacharged) return "DISLambda";
   else if(e.Mode.at(0) == "DIS" && e.Hyperon.size()) return "DISHYP"; 
   else if(e.EventHasNeutronScatter) return "Neutron";
   else return "Other";

   return type;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Get the neutrino interaction process

std::string GetProc(Event e){

   if(!e.Mode.size()) throw std::invalid_argument("GetType: Event has Mode.size() = 0, should be at least 1");

   std::string mode,ccnc;

   if(e.Mode.at(0) == "Data") return "Data";
   else if(e.Mode.at(0) == "EXT") return "EXT";
   else if(e.Mode.at(0) == "Dirt") return "Dirt";
   else if(e.EventIsSignal) return "Signal";
   else if(e.Mode.at(0) == "HYP") return "OtherHYP";      

   ccnc = e.CCNC.at(0);
   mode = e.Mode.at(0); 

   if(mode == "Diffractive" || mode == "ElectronScattering") return "Other";
   else if(ccnc == "CC") return ccnc + mode;
   else return "NC";

   return "Other";
}

};

#endif
