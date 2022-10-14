using namespace amt;
struct model{
  void preProcess(){} // not used in this example 
  
  template < class varType, class tensorType, bool storeNames>
  void operator()(amt::amtModel<varType,tensorType,storeNames> &model__){
    PARAMETER_SPD_MATRIX(P,3); 
    // Note: PARAMETER_SPD_MATRIX(P,3) really makes a parameter vector  
    // named P_internal, and subsequently constructs SPDmatrix<varType> P
    Eigen::VectorXd scaleDiag; scaleDiag.setConstant(3,4.0);
    model__ += wishartDiagScale_ld(P,scaleDiag,10.0); 
    // P has a Wishart(4*I,10.0) distribution a priori 
    model__.generated(P,"P"); // full matrix stored
    model__.generated(P.coeff(0,2),"P13"); // single element stored
  } 
}; // end of struct

