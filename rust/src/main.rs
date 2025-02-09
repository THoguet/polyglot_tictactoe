use rust::{Coordinate, PlayerSymbol};
use shapes::shapes::{Draw, Grid};

mod shapes;

fn main() {
    let mut grid = Grid::new();
    println!("{:?}", grid.draw());
    grid.play(Coordinate::new(0, 0), PlayerSymbol::X);
    println!("{:?}", grid.draw());
    println!("{:?}", grid.is_win());
    grid.play(Coordinate::new(0, 1), PlayerSymbol::X);
    println!("{:?}", grid.draw());
    println!("{:?}", grid.is_win());
    grid.play(Coordinate::new(0, 2), PlayerSymbol::X);
    println!("{:?}", grid.draw());
    println!("{:?}", grid.is_win());
}
