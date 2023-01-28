/*
	There are some issues with GoogleTest that are yet to be solved in the coming couple of days.
*/
#if 0 
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING  1

#include <gtest/gtest.h>
#include "Graph2D.h"

TEST(GRAPH2D, GRAPH2D_NORMALIZATION)
{
	// This graph is centered at (2,2) spanning between (1,1) and (3,3).
	Graph2D graph = Graph2D(NULL, vec2(0, 0), vec2(100, 100), 2, 2, 1, 1, 0, 0);
	// Validate if plotting normalized coordinate works
	// (2,2) must be (0,0) in normalized coordinates aka center of the graph
	vec2f normalized = graph.NormalizeCoordinate(2, 2);
	EXPECT_EQ(normalized.x, 0);
	EXPECT_EQ(normalized.y, 0);
}
int beginTests(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#endif 