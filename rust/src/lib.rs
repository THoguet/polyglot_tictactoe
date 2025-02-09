#[derive(PartialEq, Debug)]
pub enum PlayerSymbol {
    X,
    O,
    EMPTY,
}

impl Clone for PlayerSymbol {
    fn clone(&self) -> PlayerSymbol {
        *self
    }
}

impl Copy for PlayerSymbol {}

#[derive(Debug)]
pub struct Coordinate {
    x: u8,
    y: u8,
}

impl Coordinate {
    pub fn is_in(&self, x: u8, y: u8) -> bool {
        self.x == x && self.y == y
    }

    pub fn get_x(&self) -> u8 {
        self.x
    }

    pub fn get_y(&self) -> u8 {
        self.y
    }

    pub fn new(x: u8, y: u8) -> Coordinate {
        Coordinate { x, y }
    }
}
