#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(Dijkstras, ShortestPath) {
  Graph G;
  G.numVertices = 3;
  
  G[0].push_back(Edge(0, 1, 1));
  G[1].push_back(Edge(0, 2, 4));
  G[2].push_back(Edge(1, 3, 5));

  vector<int> previous(G.numVertices, -1);
  vector<int> distance = dijkstra_shortest_path(G, 0, previous);

  EXPECT_EQ(distance, {0, 1, 5, 10});
}

TEST(Ladder, EditDistanceWithin) {
  EXPECT_TRUE(edit_distance_within("mat", "rat", 1));
  EXPECT_FALSE(edit_distance_within("apple", "banana", 1));
}

TEST(Ladder, IsAdjacent) {
  EXPECT_TRUE(is_adjacent("mat", "rat");
  EXPECT_FALSE(is_adjacent("apple", "banana");
}

TEST(Ladder, GenerateWordLadder) {
  set<string> wordList = {"head", "heal", "teal", "tell", "tall", "tail"};
  vector<string> wordLadder = generate_word_ladder("head", "tail", wordList);

  EXPECT_EQ(wordLadder, {"head", "heal", "teal", "tell", "tall", "tail"});
}
