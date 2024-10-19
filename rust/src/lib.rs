#[derive(PartialEq)]
pub enum Cell_status {
    X,
    O,
    EMPTY,
}
pub struct Coordinate {
    x: u8,
    y: u8,
}

impl Coordinate {
    fn is_in(&self, x: u8, y: u8) -> bool {
        self.x == x && self.y == y
    }
}
