// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
// Purpose:
// Transformation from Spherical to Euclidean coordinate system
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <stdexcept>
#include <vector>
#include <cmath>
#include "journal/diagnostics.h"
#include "Spherical2Cartesian.h"


namespace Exchanger {


    Spherical2Cartesian::Spherical2Cartesian()
    {}


    Spherical2Cartesian::~Spherical2Cartesian()
    {}


    void Spherical2Cartesian::coordinate(BoundedBox& bbox) const
    {
		BoundedBox bbox_tmp(bbox);

		std::vector<double> xt(DIM),xc(DIM);

		for(int i=0; i<2; i++)
			for(int j=0; j<DIM; j++) {
				if(i==0) bbox[0][j] = 1.e27;
				if(i==1) bbox[1][j] = -1.e27;
			}

		for(int a=0; a<2; a++) {
			xt[0] = bbox_tmp[a][0];

			// Degenerate case for theta (xt[0])

			//         if((a==0) && ((bbox_tmp[0][0] < M_PI) &&(bbox_tmp[1][0] > M_PI))) xt[0]=M_PI;
			//         if((a==1) && ((bbox_tmp[0][0] < 0) &&(bbox_tmp[1][0] > 0))) xt[0]=0;

			for(int b=0; b<2; b++) {
				xt[1] = bbox_tmp[b][1];
				for(int c=0; c<2; c++) {
					xt[2] = bbox_tmp[c][2];
					xc[2] = xt[2] * cos(xt[0]);
					if( (c==1) &&  (bbox_tmp[0][0] < M_PI/2.) &&
						(bbox_tmp[1][0] > M_PI/2.) )
						xt[0] = M_PI/2.;
					xc[0] = xt[2] * sin(xt[0]) * cos(xt[1]);
					xc[1] = xt[2] * sin(xt[0]) * sin(xt[1]);

					for(int j=0;j<DIM;j++) {
						if(xc[j] < bbox[0][j]) bbox[0][j] = xc[j];
						if(xc[j] > bbox[1][j]) bbox[1][j] = xc[j];
					}

					// Degenerate case for phi (xt[1])
					if(c==1 &&  bbox_tmp[0][0] < M_PI/2. &&  bbox_tmp[1][0] > M_PI/2.)xt[0]=M_PI/2.;
					if(c==1 &&  bbox_tmp[0][1]< 0 &&  bbox_tmp[1][1]> 0)xc[0] = xt[2] * sin(xt[0]);
					if(c==1 && bbox_tmp[0][1]< M_PI/2. &&  bbox_tmp[1][1]> M_PI/2.) xc[1] = xt[2] * sin(xt[0]);
					if(c==0 &&  bbox_tmp[0][1]< M_PI && bbox_tmp[1][1]> M_PI) xc[0] = -1.*xt[2] * sin(xt[0]);
					if(c==0 &&  bbox_tmp[0][1]< 1.5*M_PI &&  bbox_tmp[1][1]> 1.5*M_PI) xc[1] = -1.*xt[2] * sin(xt[0]);

					for(int j=0;j<DIM;j++) {
						if(xc[j] < bbox[0][j]) bbox[0][j] = xc[j];
						if(xc[j] > bbox[1][j]) bbox[1][j] = xc[j];
					}

				}
			}
		}
    }


    void Spherical2Cartesian::coordinate(BoundingBox& bbox) const
    {
		BoundingBox bbox_tmp;
		for(int i=0; i<2; i++)
			for(int j=0; j<DIM; j++)
				bbox_tmp[i][j] = bbox[i][j];

		std::vector<double> xt(DIM),xc(DIM);

		for(int i=0; i<2; i++)
			for(int j=0; j<DIM; j++) {
				if(i==0) bbox[0][j] = 1.e27;
				if(i==1) bbox[1][j] = -1.e27;
			}

		for(int a=0; a<2; a++) {
			xt[0] = bbox_tmp[a][0];

			// Degenerate case for theta (xt[0])

			//         if((a==0) && ((bbox_tmp[0][0] < M_PI) &&(bbox_tmp[1][0] > M_PI))) xt[0]=M_PI;
			//         if((a==1) && ((bbox_tmp[0][0] < 0) &&(bbox_tmp[1][0] > 0))) xt[0]=0;

			for(int b=0; b<2; b++) {
				xt[1] = bbox_tmp[b][1];
				for(int c=0; c<2; c++) {
					xt[2] = bbox_tmp[c][2];
					xc[2] = xt[2] * cos(xt[0]);
					if( (c==1) &&  (bbox_tmp[0][0] < M_PI/2.) &&
						(bbox_tmp[1][0] > M_PI/2.) )
						xt[0] = M_PI/2.;
					xc[0] = xt[2] * sin(xt[0]) * cos(xt[1]);
					xc[1] = xt[2] * sin(xt[0]) * sin(xt[1]);

					for(int j=0;j<DIM;j++) {
						if(xc[j] < bbox[0][j]) bbox[0][j] = xc[j];
						if(xc[j] > bbox[1][j]) bbox[1][j] = xc[j];
					}

					// Degenerate case for phi (xt[1])
					if(c==1 &&  bbox_tmp[0][0] < M_PI/2. &&  bbox_tmp[1][0] > M_PI/2.)xt[0]=M_PI/2.;
					if(c==1 &&  bbox_tmp[0][1]< 0 &&  bbox_tmp[1][1]> 0)xc[0] = xt[2] * sin(xt[0]);
					if(c==1 && bbox_tmp[0][1]< M_PI/2. &&  bbox_tmp[1][1]> M_PI/2.) xc[1] = xt[2] * sin(xt[0]);
					if(c==0 &&  bbox_tmp[0][1]< M_PI && bbox_tmp[1][1]> M_PI) xc[0] = -1.*xt[2] * sin(xt[0]);
					if(c==0 &&  bbox_tmp[0][1]< 1.5*M_PI &&  bbox_tmp[1][1]> 1.5*M_PI) xc[1] = -1.*xt[2] * sin(xt[0]);

					for(int j=0;j<DIM;j++) {
						if(xc[j] < bbox[0][j]) bbox[0][j] = xc[j];
						if(xc[j] > bbox[1][j]) bbox[1][j] = xc[j];
					}

				}
			}
		}
    }


    void Spherical2Cartesian::coordinate(Array2D<double,DIM>& X) const
    {
		std::vector<double> xt(DIM);

		for(int i=0; i<X.size(); ++i) {

			for(int j=0; j<DIM; j++)
				xt[j] = X[j][i];

			X[0][i] = xt[2] * sin(xt[0]) * cos(xt[1]);
			X[1][i] = xt[2] * sin(xt[0]) * sin(xt[1]);
			X[2][i] = xt[2] * cos(xt[0]);
		}
    }


    void Spherical2Cartesian::vector(Array2D<double,DIM>& V,
									 const Array2D<double,DIM>& X) const
    {
		std::vector<double> vt(DIM);
		std::vector<double> xt(DIM);

		// sanity check
		if(V.size() != X.size()) {
			journal::firewall_t firewall("Spherical2Cartesian");
			firewall << journal::at(__HERE__)
					 << "size of vectors mismatch" << journal::endl;
			throw std::out_of_range("Spherical2Cartesian");
		}

		for(int i=0; i<V.size(); ++i) {

			for(int j=0; j<DIM; j++) {
				vt[j] = V[j][i];
				xt[j] = X[j][i];
			}

			V[0][i] = cos(xt[0]) * cos(xt[1]) * vt[0]
				- sin(xt[1]) * vt[1]
				+ sin(xt[0]) * cos(xt[1]) * vt[2];
			V[1][i] = cos(xt[0]) * sin(xt[1]) * vt[0]
				+ cos(xt[1]) * vt[1]
				+ sin(xt[0]) * sin(xt[1]) * vt[2];
			V[2][i] = -sin(xt[0]) * vt[0]
				+ cos(xt[0]) * vt[2];
		}
    }


    void Spherical2Cartesian::tensor_rank2(Array2D<double,STRESS_DIM>& S,
										   const Array2D<double,DIM>& X) const
    {
		std::vector<double> xt(DIM);
		double Cc[3][3];
		double S_sph[3][3], S_cart[3][3];

		// sanity check
		if(S.size() != X.size()) {
			journal::firewall_t firewall("Spherical2Cartesian");
			firewall << journal::at(__HERE__)
					 << "size of vectors mismatch" << journal::endl;
			throw std::out_of_range("Spherical2Cartesian");
		}

		for(int i=0; i<S.size(); ++i) {
			S_sph[0][0] = S[0][i];
			S_sph[1][1] = S[1][i];
			S_sph[2][2] = S[2][i];
			S_sph[0][1] = S[3][i];
			S_sph[0][2] = S[4][i];
			S_sph[1][2] = S[5][i];
			S_sph[1][0] = S_sph[0][1];
			S_sph[2][0] = S_sph[0][2];
			S_sph[2][1] = S_sph[1][2];
			for(int k=0; k<DIM; k++) {
				for(int j=0; j<DIM; j++) {
					S_cart[k][j] = 0.0;
				}
			}
			for(int j=0; j<DIM; j++)
				xt[j] = X[j][i];

			Cc[0][0] = cos(xt[0])*cos(xt[1]);
			Cc[1][0] = cos(xt[0])*sin(xt[1]);
			Cc[2][0] = -sin(xt[0]);
			Cc[0][1] = -sin(xt[1]);
			Cc[1][1] = cos(xt[1]);
			Cc[2][1] = 0.0;
			Cc[0][2] = sin(xt[0])*cos(xt[1]);
			Cc[1][2] = sin(xt[0])*sin(xt[1]);
			Cc[2][2] = cos(xt[0]);

			for(int k=0; k<DIM; k++) {
				for(int j=0; j<DIM; j++) {
					for(int m=0; m<DIM; m++) {
						for(int n=0; n<DIM; n++) {
							// S_cart[k][j] = Cc[k][m]*S_sph[m][n]*transpose(Cc)[n][j]
							//              = Cc[k][m]*S_sph[m][n]*Cc[j][n]
							S_cart[k][j] += Cc[k][m]*S_sph[m][n]*Cc[j][n];
						}
					}
				}
			}
			S[0][i] = S_cart[0][0];
			S[1][i] = S_cart[1][1];
			S[2][i] = S_cart[2][2];
			S[3][i] = S_cart[0][1];
			S[4][i] = S_cart[0][2];
			S[5][i] = S_cart[1][2];
		}
	}

// Transformation from Euclidean to Spherical coordinate system

    void Spherical2Cartesian::xcoordinate(BoundedBox& bbox) const
    {
		BoundedBox bbox_tmp(bbox);
		double minrad;
		std::vector<double> xt(DIM), xc(DIM);
		for(int i=0; i<2; i++)
			for(int j=0; j<DIM; j++) {
				if(i==0) bbox[0][j] = 1.e27;
				if(i==1) bbox[1][j] = -1.e27;
				minrad = 1.e27;
			}

		for(int a=0; a<2; a++) {
			xt[0] = bbox_tmp[a][0];

			for(int b=0; b<2; b++) {
				xt[1] = bbox_tmp[b][1];
				for(int c=0; c<2; c++) {
					xt[2] = bbox_tmp[c][2];

					xc[2] = std::sqrt(xt[0]*xt[0] + xt[1]*xt[1] + xt[2]*xt[2]);
					xc[1] = std::atan2(xt[1], xt[0]);
					xc[0] = std::acos(xt[2] / xc[2]);

					for(int j=0;j<DIM;j++) {

						if(minrad > fabs(xt[j])) minrad = fabs(xt[j]);
						if(xc[j] < bbox[0][j]) bbox[0][j] = xc[j];
						if(xc[j] > bbox[1][j]) bbox[1][j] = xc[j];
					}

				}
			}
		}
		bbox[0][2] = minrad;
    }


    void Spherical2Cartesian::xcoordinate(BoundingBox& bbox) const
    {
		BoundingBox bbox_tmp;
		for(int i=0; i<2; i++)
			for(int j=0; j<DIM; j++)
				bbox_tmp[i][j] = bbox[i][j];

		double minrad;
		std::vector<double> xt(DIM), xc(DIM);
		for(int i=0; i<2; i++)
			for(int j=0; j<DIM; j++) {
				if(i==0) bbox[0][j] = 1.e27;
				if(i==1) bbox[1][j] = -1.e27;
				minrad = 1.e27;
			}

		for(int a=0; a<2; a++) {
			xt[0] = bbox_tmp[a][0];

			for(int b=0; b<2; b++) {
				xt[1] = bbox_tmp[b][1];
				for(int c=0; c<2; c++) {
					xt[2] = bbox_tmp[c][2];

					xc[2] = std::sqrt(xt[0]*xt[0] + xt[1]*xt[1] + xt[2]*xt[2]);
					xc[1] = std::atan2(xt[1], xt[0]);
					xc[0] = std::acos(xt[2] / xc[2]);

					for(int j=0;j<DIM;j++) {

						if(minrad > fabs(xt[j])) minrad = fabs(xt[j]);
						if(xc[j] < bbox[0][j]) bbox[0][j] = xc[j];
						if(xc[j] > bbox[1][j]) bbox[1][j] = xc[j];
					}

				}
			}
		}
		bbox[0][2] = minrad;
    }


    void Spherical2Cartesian::xcoordinate(Array2D<double,DIM>& X) const
    {
		std::vector<double> xt(DIM);

		for(int i=0; i<X.size(); ++i) {

			for(int j=0; j<DIM; j++)
				xt[j] = X[j][i];

			X[2][i] = std::sqrt(xt[0]*xt[0] + xt[1]*xt[1] + xt[2]*xt[2]);
			X[1][i] = std::atan2(xt[1], xt[0]);
			X[0][i] = std::acos(xt[2] / X[2][i]);
		}
    }


    void Spherical2Cartesian::xvector(Array2D<double,DIM>& V,
									  const Array2D<double,DIM>& X) const
    {
		std::vector<double> vt(DIM);
		std::vector<double> xt(DIM);

		// sanity check
		if(V.size() != X.size()) {
			journal::firewall_t firewall("Spherical2Cartesian");
			firewall << journal::at(__HERE__)
					 << "size of vectors mismatch" << journal::endl;
			throw std::out_of_range("Spherical2Cartesian");
		}

		for(int i=0; i<V.size(); ++i) {

			for(int j=0; j<DIM; j++) {
				vt[j] = V[j][i];
				xt[j] = X[j][i];
			}

			V[0][i] = cos(xt[0]) * cos(xt[1]) * vt[0]
				+ cos(xt[0]) * sin(xt[1]) * vt[1]
				- sin(xt[0]) * vt[2];
			V[1][i] = -sin(xt[0]) * vt[0]
				+ cos(xt[1]) * vt[1];
			V[2][i] = sin(xt[0]) * cos(xt[1]) * vt[0]
				+ sin(xt[0]) * sin(xt[1]) * vt[1]
				+ cos(xt[0]) * vt[2];
		}
    }

    void Spherical2Cartesian::xtensor_rank2(Array2D<double,STRESS_DIM>& S,
										   const Array2D<double,DIM>& X) const
    {
		std::vector<double> xt(DIM);
		double Cc[3][3];
		double S_sph[3][3], S_cart[3][3];

		// sanity check
		if(S.size() != X.size()) {
			journal::firewall_t firewall("Spherical2Cartesian");
			firewall << journal::at(__HERE__)
					 << "size of vectors mismatch" << journal::endl;
			throw std::out_of_range("Spherical2Cartesian");
		}

		for(int i=0; i<S.size(); ++i) {
			S_cart[0][0] = S[0][i];
			S_cart[1][1] = S[1][i];
			S_cart[2][2] = S[2][i];
			S_cart[0][1] = S[3][i];
			S_cart[0][2] = S[4][i];
			S_cart[1][2] = S[5][i];
			S_cart[1][0] = S_cart[0][1];
			S_cart[2][0] = S_cart[0][2];
			S_cart[2][1] = S_cart[1][2];
			for(int k=0; k<DIM; k++) {
				for(int j=0; j<DIM; j++) {
					S_sph[k][j] = 0.0;
				}
			}
			for(int j=0; j<DIM; j++)
				xt[j] = X[j][i];

			Cc[0][0] = cos(xt[0])*cos(xt[1]);
			Cc[1][0] = cos(xt[0])*sin(xt[1]);
			Cc[2][0] = -sin(xt[0]);
			Cc[0][1] = -sin(xt[1]);
			Cc[1][1] = cos(xt[1]);
			Cc[2][1] = 0.0;
			Cc[0][2] = sin(xt[0])*cos(xt[1]);
			Cc[1][2] = sin(xt[0])*sin(xt[1]);
			Cc[2][2] = cos(xt[0]);

			for(int k=0; k<DIM; k++) {
				for(int j=0; j<DIM; j++) {
					for(int m=0; m<DIM; m++) {
						for(int n=0; n<DIM; n++) {
							// S_sph[k][j] = transpose(Cc)[k][m]*S_cart[m][n]*Cc[n][j]
							//              = Cc[m][k]*S_cart[m][n]*Cc[n][j]
							S_sph[k][j] += Cc[m][k]*S_cart[m][n]*Cc[n][j];
						}
					}
				}
			}
			S[0][i] = S_sph[0][0];
			S[1][i] = S_sph[1][1];
			S[2][i] = S_sph[2][2];
			S[3][i] = S_sph[0][1];
			S[4][i] = S_sph[0][2];
			S[5][i] = S_sph[1][2];
		}
	}

}
// version
// $Id: Spherical2Cartesian.cc,v 1.6 2005/06/03 21:51:47 leif Exp $

// End of file
