#pragma once

#include "context.h"

/**
 * Initial parameters for each plummer lens.
 */

/**
 * Context for multiplane plummer calculations.
 *
 * For sample use cases see api_tests.cu in tests/ or example.cpp in
 * example/ for a complete example program.
 */
class CPUMultiPlaneContext {
  private:
    const double m_angularUnit;
    const Cosmology m_cosmology;
    Vector2D<float> *m_theta;
    size_t m_theta_len;
    std::vector<size_t> m_theta_count;
    Vector2D<float> *m_beta;
    Multiplane *m_multiplane;
    std::vector<std::vector<Vector2D<float>>> m_betas;

    CompositeLensBuilder buildLens(const float redshift,
                                   const std::vector<PlummerParams> &params);

  public:
    /**
     * Create a new context.
     *
     * @param angularUnit What unit is used in the input data,
     * eg. ANGLE_ARCSEC.
     * @param cosmology What parameters are used for cosmology.
     */
    CPUMultiPlaneContext(const double angularUnit, const Cosmology cosmology);
    ~CPUMultiPlaneContext();

    /**
     * Initialize lenses and source planes.
     *
     * @param lensRedshifts List of redshifts for each lens.
     * @param params Parameters for lenses, must be the same length as
     * lensRedshifts.
     * @param sourceRedshifts List of source plane redshifts.
     */
    int init(const std::vector<float> &lensRedshifts,
             const std::vector<std::vector<PlummerParams>> &params,
             const std::vector<float> &sourceRedshifts);

    /**
     * Set thetas for calculations.
     *
     * @param thetas List of thetas per source plane.
     */
    int setThetas(const std::vector<std::vector<Vector2D<float>>> &thetas);

    /**
     * Calculation beta positions with lens masses.
     */
    int
    calculatePositionsBenchmark(const std::vector<std::vector<float>> &masses,
                                float &millis, int nruns = 7);

    const std::vector<Vector2D<float>> &getSourcePositions(int idx) const;
};