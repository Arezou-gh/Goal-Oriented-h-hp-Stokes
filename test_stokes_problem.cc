#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "StokesProblem.hh"
#include "Parameters.hh"

TEST_CASE("convergence rate 1", "[StokesProblem]")
{
  Parameters parameters("test_project.inp");
  StokesProblem<2> stokes_problem(parameters);
  stokes_problem.generate_mesh();
  double old_error(0.);
  double new_error(0.);
  for (unsigned int i=0; i<4; ++i)
    {
      old_error = new_error;
      stokes_problem.get_triangulation().refine_global(1);
      stokes_problem.setup_system(primal);
      stokes_problem.assemble_system(primal);
      stokes_problem.solve(primal);
      stokes_problem.compute_error();
      new_error = stokes_problem.error_l2_norm();
    }

  REQUIRE(std::abs((old_error/new_error)-8.) < 0.1);
}

TEST_CASE("convergence rate 2", "[StokesProblem]")
{
  Parameters parameters("test_project.inp");
  parameters.set_example(example_3);
  StokesProblem<2> stokes_problem(parameters);
  stokes_problem.generate_mesh();
  double old_error(0.);
  double new_error(0.);
  for (unsigned int i=0; i<6; ++i)
    {
      old_error = new_error;
      stokes_problem.get_triangulation().refine_global(1);
      stokes_problem.setup_system(primal);
      stokes_problem.assemble_system(primal);
      stokes_problem.solve(primal);
      stokes_problem.compute_error();
      new_error = stokes_problem.error_l2_norm();
    }

  REQUIRE(std::abs((old_error/new_error)-8.) < 0.1);
}

TEST_CASE("3D problem", "[StokesProblem]")
{
  Parameters parameters("test_project.inp");
  parameters.set_example(example_5);
  StokesProblem<2> stokes_problem(parameters);
  stokes_problem.generate_mesh();
  stokes_problem.get_triangulation().refine_global(1);
  stokes_problem.setup_system(primal);
  stokes_problem.assemble_system(primal);
  stokes_problem.solve(primal);
}
