// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// rcpp_clipper
Rcpp::DataFrame rcpp_clipper(const Rcpp::List upper_layer, const Rcpp::List lower_layer);
RcppExport SEXP _moveability_rcpp_clipper(SEXP upper_layerSEXP, SEXP lower_layerSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::List >::type upper_layer(upper_layerSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List >::type lower_layer(lower_layerSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_clipper(upper_layer, lower_layer));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_get_sp_dists_par
Rcpp::NumericVector rcpp_get_sp_dists_par(const Rcpp::DataFrame graph, const Rcpp::DataFrame vert_map_in, Rcpp::IntegerVector fromi, const double d_threshold, const std::string& heap_type);
RcppExport SEXP _moveability_rcpp_get_sp_dists_par(SEXP graphSEXP, SEXP vert_map_inSEXP, SEXP fromiSEXP, SEXP d_thresholdSEXP, SEXP heap_typeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::DataFrame >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::DataFrame >::type vert_map_in(vert_map_inSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type fromi(fromiSEXP);
    Rcpp::traits::input_parameter< const double >::type d_threshold(d_thresholdSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type heap_type(heap_typeSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_get_sp_dists_par(graph, vert_map_in, fromi, d_threshold, heap_type));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_moveability_rcpp_clipper", (DL_FUNC) &_moveability_rcpp_clipper, 2},
    {"_moveability_rcpp_get_sp_dists_par", (DL_FUNC) &_moveability_rcpp_get_sp_dists_par, 5},
    {NULL, NULL, 0}
};

RcppExport void R_init_moveability(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
