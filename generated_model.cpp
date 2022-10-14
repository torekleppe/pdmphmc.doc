
using namespace amt;

double quadNorm(const Eigen::VectorXd& x){
  return(x.dot(x));
}

struct model{
  void preProcess(){} // not used in this example 
  template < class varType, class tensorType, bool storeNames>
  void operator()(amt::amtModel<varType,tensorType,storeNames> &model__){
    
    PARAMETER_VECTOR(x,4); // parameter (sampled quantity)
    model__+=normal_ld(x,0.0,1.0); // add standard normal log-density
    
    
    // make the whole parameter a generated
    model__.generated(x,"x_gen"); 
    // different transformations of x to be recored:
    model__.generated(std::pow(asDouble(x(0)),3),"x1_cube");
    model__.generated(exp(asDouble(x(1))),"x2_exp");
    
    double qn = quadNorm(asDouble(x));
    model__.generated(qn,"quadraticNorm");
    
  } 
}; // end of struct

