
using namespace amt;
struct model{
  
  DATA_VECTOR(y); // data to be passed from R
  
  void preProcess(){} // not used in this example 
  
  template < class varType, class tensorType, bool storeNames>
  void operator()(amt::amtModel<varType,tensorType,storeNames> &model__){
    
    PARAMETER_SCALAR(mu); // parameter (sampled quantity)
    PARAMETER_SCALAR(lambda); // parameter (sampled quantity)
    // note; all variables depending on the parameters must be of type varType
    varType sigma = exp(0.5*lambda);
    // add data likelihood to the model object
    model__+=normal_ld(y,mu,sigma);
    // add sigma as a quantity to produce samples of
    model__.generated(sigma,"sigma");
  } 
}; // end of struct

