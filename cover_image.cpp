
using namespace amt;
struct model{
  Eigen::VectorXd init;
  
  void preProcess(){
    init.resize(2);
    init(0) = -0.001;
    init(1) = -0.01;
  }
  
  template < class varType, class tensorType, bool storeNames>
  void operator()(amt::amtModel<varType,tensorType,storeNames> &model__){
    
    
    PARAMETER_VECTOR(x,2,init); 
    
    //model__+=normal_ld(0.5*x(0)*x(0)+x(1)*x(1) + 0.4*x(0)*x(1)-1.0,0.0,0.3);
    //model__+=normal_ld(x(0),0.0,100.0);
    //model__+=normal_ld(x(1),0.0,100.0);
    
    model__+=normal_ld(x(0),0.0,1.0);
    model__+=normal_ld(x(1),x(0)*x(0),0.2);
    
  } 
}; // end of struct

