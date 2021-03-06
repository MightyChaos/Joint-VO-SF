
/*********************************************************************************
**Fast Odometry and Scene Flow from RGB-D Cameras based on Geometric Clustering	**
**------------------------------------------------------------------------------**
**																				**
**	Copyright(c) 2017, Mariano Jaimez Tarifa, University of Malaga & TU Munich	**
**	Copyright(c) 2017, Christian Kerl, TU Munich								**
**	Copyright(c) 2017, MAPIR group, University of Malaga						**
**	Copyright(c) 2017, Computer Vision group, TU Munich							**
**																				**
**  This program is free software: you can redistribute it and/or modify		**
**  it under the terms of the GNU General Public License (version 3) as			**
**	published by the Free Software Foundation.									**
**																				**
**  This program is distributed in the hope that it will be useful, but			**
**	WITHOUT ANY WARRANTY; without even the implied warranty of					**
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the				**
**  GNU General Public License for more details.								**
**																				**
**  You should have received a copy of the GNU General Public License			**
**  along with this program. If not, see <http://www.gnu.org/licenses/>.		**
**																				**
*********************************************************************************/

#include <string.h>
#include "joint_vo_sf.h"


// -------------------------------------------------------------------------------
//								Instructions:
// Set the flag "save_results" to true if you want to save the estimated scene
// flow and the static/dynamic segmentation
// -------------------------------------------------------------------------------

int main()
{
	const bool save_results = true;
	const unsigned int res_factor = 2;
	VO_SF cf(res_factor, 1.4*704, 1.4*704, 704, 384);

	//Set image dir
	std::string dir = "/home/chaoyang/deepSLAM/";
		// std::string dir = "../data/person standing/";

	//Load images and create both pyramids
	cf.loadImagePairFromFiles(dir, res_factor);

	//Create the 3D Scene
	cf.initializeSceneCamera();

	//Run the algorithm
	cf.run_VO_SF(false);
    cf.createImagesOfSegmentations();

	//Update the 3D scene
	cf.updateSceneCamera(false);

	//Save results?
	if (save_results)
		cf.saveFlowAndSegmToFile(dir);

	mrpt::system::os::getch();
	return 0;
}
