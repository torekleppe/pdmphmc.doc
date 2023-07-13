

class nonLinFun : public constraintFunctor {
public:
  // evaluates F only
  inline double operator()(const Eigen::VectorXd& arg) const {
    return(1.0 - arg(0)*arg(1)); 
  }
  // evaluates F and the gradient of F stored in grad
  inline double operator()(const Eigen::VectorXd& arg,
                         Eigen::VectorXd& grad) const {
    if(grad.size()!=arg.size()) grad.resize(arg.size());
    grad.setZero();
    grad(0) = -arg(1);
    grad(1) = -arg(0); // gradient of F
    return(operator()(arg)); // return value of F itself
  }
  // arbitrary name
  inline std::string name() const {return "some_constraint_functor";}
};


using namespace amt;
struct model{
  
  nonLinFun functor_;
  
  DATA_INT(constrType); // which constraint type to use, passed from R
  
  void preProcess(){} // not used in this example 
  
  template < class varType, class tensorType, bool storeNames>
  void operator()(amt::amtModel<varType,tensorType,storeNames> &model__){
    
    
    PARAMETER_VECTOR(x,2); // parameter (sampled quantity)
    // x is bivariate normally distributed with correlation rho
    // before any constraints are imposed
    double rho = 0.7;
    model__+=normal_ld(x(0),0.0,1.0);
    model__+=normal_ld(x(1),rho*x(0),sqrt(1.0-rho*rho));
    
    // now add the different constraints
    if(constrType==1){
      model__.linConstraint(1.0-x(0)-x(1));
    } else if(constrType==2){
      model__.sparseLinConstraint(1.0-x(0)-x(1));
    } else if(constrType==3){
      VectorXv z = x;
      z(0)-=0.5;
      z(1)-=0.25;
      model__.sparseLinL1Constraint(z,2.0);
    } else if(constrType==4){
      VectorXv z(x.size());
      z(0) = x(0) + 0.5;
      z(1) = 2.0*x(1) - 0.5*x(0) - 0.25;
      model__.sparseLinL2Constraint(z,2.0);
    } else if(constrType==5){
      model__.sparseLinFunConstraint(x,functor_);
    }
  } 
}; // end of struct

