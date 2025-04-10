#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "queue.hpp"
#include "PathFinder.hpp"
#include <chrono>

/* Provided test cases */
TEST_CASE("PathFinder: Test Queue ADT enqueue, deque, peekFront", "[queue]")
{
    Queue<int, List<int>> queue;

    REQUIRE(queue.isEmpty());
    queue.enqueue(12);
    REQUIRE_FALSE(queue.isEmpty());

    queue.enqueue(13);
    queue.enqueue(14);

    REQUIRE(queue.peekFront() == 12);
    queue.dequeue();

    REQUIRE(queue.peekFront() == 13);
    queue.dequeue();

    REQUIRE(queue.peekFront() == 14);
    queue.dequeue();
    REQUIRE(queue.isEmpty());
    REQUIRE_THROWS_AS(queue.peekFront(), std::out_of_range);
    REQUIRE_THROWS_AS(queue.dequeue(), std::out_of_range);
}
// Need to at least pass this test case for draft deadline
TEST_CASE("PathFinder: Testing constructor on invalid images", "[pathfinder]")
{
    // Create an simple image with invalid pixel colors
    Image<Pixel> img(3, 3);
    img(0, 0) = WHITE;
    img(0, 1) = WHITE;
    img(0, 2) = WHITE;
    img(1, 0) = WHITE;
    img(1, 1) = BLUE; // Invalid color
    img(1, 2) = WHITE;
    img(2, 0) = WHITE;
    img(2, 1) = WHITE;
    img(2, 2) = WHITE;

    // Check if the constructor throws an exception
    REQUIRE_THROWS_AS(PathFinder pathFinder(img), std::invalid_argument);

    img(1, 1) = WHITE; // all white, no red pixel
    REQUIRE_THROWS_AS(PathFinder pathFinder(img), std::invalid_argument);

    img(1, 1) = RED; // all white but one red pixel
    img(1, 2) = RED; // two red pixels now
    REQUIRE_THROWS_AS(PathFinder pathFinder(img), std::invalid_argument);

    img(1, 2) = BLACK; // all white but one red pixel, one black pixel
    REQUIRE_NOTHROW(PathFinder pathFinder(img));

    Image<Pixel> img2 = readFromFile("../tests/maze00_extra_color.png");
    REQUIRE_THROWS_AS(PathFinder PathFinder(img2), std::invalid_argument);

    Image<Pixel> img3 = readFromFile("../tests/maze00_no_start.png");
    REQUIRE_THROWS_AS(PathFinder PathFinder(img3), std::invalid_argument);

    Image<Pixel> img4 = readFromFile("../tests/maze00_extra_start.png");
    REQUIRE_THROWS_AS(PathFinder PathFinder(img4), std::invalid_argument);
}

TEST_CASE("PathFinder: Test getStart()", "[pathfinder]")
{
    // Create a simple image with one red pixel
    Image<Pixel> img(3, 3);
    img(0, 0) = WHITE;
    img(0, 1) = WHITE;
    img(0, 2) = WHITE;
    img(1, 0) = WHITE;
    img(1, 1) = RED; // Red pixel
    img(1, 2) = WHITE;
    img(2, 0) = WHITE;
    img(2, 1) = WHITE;
    img(2, 2) = WHITE;

    // Create a PathFinder object
    PathFinder pathFinder(img);

    // Check if the start coordinate is set correctly
    REQUIRE(pathFinder.getStart() == Coord(1, 1));
}

TEST_CASE("PathFinder: Test Pathfinding Result and Time", "[pathfinder]")
{
    Image<Pixel> img0 = readFromFile("../tests/maze00.png");
    REQUIRE_NOTHROW(PathFinder my_solver0(img0));

    PathFinder my_solver(img0);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    my_solver.findPath();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time for Pathfinding of maze00: " << elapsed_seconds.count() << "s\n";

    my_solver.writeSolutionToFile("../tests/myoutput00_NSWE.png");

    // Check if the output image correctly identifies the exit
    REQUIRE(compareImagesExit("../tests/output00_NSWE.png", "../tests/myoutput00_NSWE.png"));

    // Clear and reinitialize the solver using different strategy
    my_solver.clear();
    my_solver.load(img0);
    my_solver.findPath("WENS");
    my_solver.writeSolutionToFile("../tests/myoutput00_WENS.png");

    // Check if the output image correctly identifies the exit
    REQUIRE(compareImagesExit("../tests/output00_WENS.png", "../tests/myoutput00_WENS.png"));

    Image<Pixel> img1 = readFromFile("../tests/maze01.png");
    my_solver.clear();
    my_solver.load(img1);
    // maze01 is unfindble
    REQUIRE_THROWS_AS(my_solver.findPath(), std::runtime_error);
    my_solver.clear();

    Image<Pixel> img2 = readFromFile("../tests/maze02.png");
    my_solver.load(img2);

    start = std::chrono::steady_clock::now();
    my_solver.findPath();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Elapsed time for Pathfinding of maze02: " << elapsed_seconds.count() << "s\n";

    my_solver.writeSolutionToFile("../tests/myoutput02_NSWE.png");
    // Check if the output image is correct
    REQUIRE(compareImagesExit("../tests/output02_NSWE.png", "../tests/myoutput02_NSWE.png"));
    my_solver.clear();
}

// Usage of findPathWithVisualization, not included in grader
TEST_CASE("PathFinder: Demo Pathfinding Gif Creation", "[pathfinder]")
{
    Image<Pixel> img0 = readFromFile("../tests/maze00.png");
    PathFinder my_solver(img0);

    // Create a GIF file with the pathfinding visualization
    // It creates a myoutput00.gif with EVERY 1 movement and 200ms display for each movement
    // BLUE pixels show the frontier changes along the search
    // It also creates a myoutput00_final_visual.png with the final path
    my_solver.findPathWithVisualization("../tests/myoutput00", 20, 1);
    my_solver.clear();

    Image<Pixel> img1 = readFromFile("../tests/maze01.png");
    my_solver.load(img1);
    // maze01 is large, so display EVERY 50 movements (one frame) and 50ms display for each frame
    // This would fail but partial attempt visualization is recorded
    REQUIRE_THROWS(my_solver.findPathWithVisualization("../tests/myoutput01", 5, 50)); // THROW AN EXCEPTION
    my_solver.clear();

    // A larger size but solvable maze
    // A gif and final_visual image are created
    Image<Pixel> img2 = readFromFile("../tests/maze02.png");
    my_solver.load(img2);
    my_solver.findPathWithVisualization("../tests/myoutput02", 5, 50);
    my_solver.clear();
}

/* Write your own uint tests here*/



TEST_CASE("test 1: constructor and getstart basic functionality", "[pathfinder]") {
    Image<Pixel> img(3, 3);
    img(1, 1) = RED;
    PathFinder pf(img);

    REQUIRE(pf.getStart() == Coord(1, 1));
}

TEST_CASE("test 2: constructor throws for invalid pixel color", "[pathfinder]") {
    Image<Pixel> img(2, 2);
    img(0, 0) = WHITE;
    img(0, 1) = BLACK;
    img(1, 0) = BLUE; // invalid color
    img(1, 1) = RED;

    REQUIRE_THROWS_AS(PathFinder pf(img), std::invalid_argument);
}

TEST_CASE("test 3: constructor throws when no red pixel found", "[pathfinder]") {
    Image<Pixel> img(2, 2);
    img(0, 0) = WHITE;
    img(0, 1) = BLACK;
    img(1, 0) = WHITE;
    img(1, 1) = BLACK;

    REQUIRE_THROWS_AS(PathFinder pf(img), std::invalid_argument);
}

TEST_CASE("test 4: constructor throws for multiple red pixels", "[pathfinder]") {
    Image<Pixel> img(2, 2);
    img(0, 0) = RED;
    img(1, 1) = RED;
    img(0, 1) = WHITE;
    img(1, 0) = WHITE;

    REQUIRE_THROWS_AS(PathFinder pf(img), std::invalid_argument);
}

TEST_CASE("test 5: findpath on trivial 1x1 image", "[pathfinder]") {
    Image<Pixel> img(1, 1);
    img(0, 0) = RED;

    PathFinder pf(img);
    REQUIRE_NOTHROW(pf.findPath());
    REQUIRE(pf.getEnd() == Coord(0, 0));
}

TEST_CASE("test 6: path not found should throw", "[pathfinder]") {
    Image<Pixel> img(3, 3);
    img(1, 1) = RED;
    img(0, 1) = BLACK;
    img(1, 0) = BLACK;
    img(1, 2) = BLACK;
    img(2, 1) = BLACK;

    PathFinder pf(img);
    REQUIRE_THROWS_AS(pf.findPath(), std::runtime_error);
}

TEST_CASE("test 7: check image validation catches extra red", "[pathfinder]") {
    Image<Pixel> img(3, 3);
    img(0, 0) = RED;
    img(2, 2) = RED;
    REQUIRE_THROWS_AS(PathFinder pf(img), std::invalid_argument);
}

TEST_CASE("test 8: check image validation catches illegal color", "[pathfinder]") {
    Image<Pixel> img(3, 3);
    img(1, 1) = RED;
    img(0, 0) = BLUE;  // invalid
    REQUIRE_THROWS_AS(PathFinder pf(img), std::invalid_argument);
}

TEST_CASE("test 9: valid white path with correct coloring", "[pathfinder]") {
    Image<Pixel> img(3, 3);
    img(1, 1) = RED;
    img(1, 2) = WHITE;
    img(1, 0) = WHITE;
    img(0, 1) = WHITE;

    PathFinder pf(img);
    REQUIRE_NOTHROW(pf.findPath("NSEW"));
}

TEST_CASE("test 10: findpath follows given strategy", "[pathfinder]") {
    Image<Pixel> img(4, 4);
    img(2, 2) = RED;
    img(2, 3) = WHITE;
    img(3, 3) = WHITE;

    PathFinder pf(img);
    pf.findPath("ESWN");

    REQUIRE(pf.getEnd() == Coord(3, 3));
}

TEST_CASE("test 11: findpath throws when surrounded by black", "[pathfinder]") {
    Image<Pixel> img(3, 3);
    img(1, 1) = RED;
    img(0, 1) = BLACK;
    img(1, 0) = BLACK;
    img(1, 2) = BLACK;
    img(2, 1) = BLACK;

    PathFinder pf(img);
    REQUIRE_THROWS_AS(pf.findPath("NSWE"), std::runtime_error);
}

TEST_CASE("test 12: queue basic enqueue dequeue peek", "[queue]") {
    Queue<int, List<int>> q;

    REQUIRE(q.isEmpty());
    q.enqueue(5);
    q.enqueue(10);
    REQUIRE_FALSE(q.isEmpty());
    REQUIRE(q.peekFront() == 5);
    q.dequeue();
    REQUIRE(q.peekFront() == 10);
    q.dequeue();
    REQUIRE(q.isEmpty());
    REQUIRE_THROWS_AS(q.peekFront(), std::out_of_range);
}

TEST_CASE("test 13: full path from center to border", "[pathfinder]") {
    Image<Pixel> img(5, 5);
    for (int x = 0; x < 5; ++x)
        for (int y = 0; y < 5; ++y)
            img(x, y) = WHITE;

    img(2, 2) = RED;
    img(0, 2) = WHITE;  

    PathFinder pf(img);
    pf.findPath("NSWE");

    REQUIRE(pf.getEnd() == Coord(0, 2));
}