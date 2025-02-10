#[derive(PartialEq, Debug)]
pub enum PlayerSymbol {
    X,
    O,
    EMPTY,
}

impl PlayerSymbol {
    pub fn from_char(symbol: char) -> Result<PlayerSymbol, &'static str> {
        if symbol == 'X' {
            return Ok(PlayerSymbol::X);
        } else if symbol == 'O' {
            return Ok(PlayerSymbol::O);
        }
        Err("Symbol not valid.")
    }
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

pub mod shapes {

    use crate::{Coordinate, PlayerSymbol};

    #[derive(Debug)]
    pub struct Cell {
        current_player_symbol: PlayerSymbol,
    }

    #[derive(Debug)]
    pub struct Grid {
        cells: [[Cell; 3]; 3],
        rows: [Row; 8],
        next_player: PlayerSymbol,
    }

    #[derive(Debug)]
    pub struct Row {
        cell_indices: [(usize, usize); 3],
    }

    impl Row {
        // all cells must be the same symbol != empty
        fn is_win(&self, grid: &Grid) -> bool {
            let (r0, c0) = self.cell_indices[0];
            let first_symbol = grid.cells[r0][c0].current_player_symbol;
            if first_symbol == PlayerSymbol::EMPTY {
                return false;
            }
            for &(r, c) in &self.cell_indices {
                if grid.cells[r][c].current_player_symbol != first_symbol {
                    return false;
                }
            }
            true
        }
    }

    impl Cell {
        fn new() -> Cell {
            Cell {
                current_player_symbol: PlayerSymbol::EMPTY,
            }
        }

        fn play(&mut self, p: PlayerSymbol) -> bool {
            if self.current_player_symbol != PlayerSymbol::EMPTY {
                return false;
            }
            self.current_player_symbol = p;
            return true;
        }
    }

    impl Draw for Grid {
        fn draw(&self) {
            let mut cpt = 0;
            for cell in &self.cells {
                if cpt == 0 {
                    print!("XY 0 1 2\n");
                }
                print!("{cpt:?} |");
                for c in cell {
                    if c.current_player_symbol == PlayerSymbol::EMPTY {
                        print!(" ");
                    } else {
                        print!("{:?}", c.current_player_symbol);
                    }
                    print!("|");
                }
                println!();
                cpt += 1;
            }
        }
    }

    impl Grid {
        pub fn is_win(&self) -> bool {
            for row in &self.rows {
                if row.is_win(self) {
                    return true;
                }
            }
            return false;
        }

        pub fn next(&mut self) -> PlayerSymbol {
            let next_player = self.next_player;
            if self.next_player == PlayerSymbol::X {
                self.next_player = PlayerSymbol::O;
            } else {
                self.next_player = PlayerSymbol::X
            }
            next_player
        }

        pub fn get_cell(&mut self, x: usize, y: usize) -> Result<&mut Cell, &'static str> {
            if x >= 3 || y >= 3 {
                return Err("not a valid cell");
            }
            Ok(&mut self.cells[x][y])
        }

        /// Play for the player on coordinate c, return true if the action is successful
        pub fn play(&mut self, c: Coordinate, player: PlayerSymbol) -> bool {
            if player == PlayerSymbol::EMPTY {
                return false;
            }
            let cell = match self.get_cell(c.get_x() as usize, c.get_y() as usize) {
                Ok(cell) => cell,
                Err(_) => return false,
            };
            cell.play(player)
        }

        pub fn new() -> Grid {
            let new_cells: [[Cell; 3]; 3] = [
                [Cell::new(), Cell::new(), Cell::new()],
                [Cell::new(), Cell::new(), Cell::new()],
                [Cell::new(), Cell::new(), Cell::new()],
            ];
            let rows = [
                Row {
                    cell_indices: [(0, 0), (0, 1), (0, 2)],
                },
                Row {
                    cell_indices: [(1, 0), (1, 1), (1, 2)],
                },
                Row {
                    cell_indices: [(2, 0), (2, 1), (2, 2)],
                },
                Row {
                    cell_indices: [(0, 0), (1, 0), (2, 0)],
                },
                Row {
                    cell_indices: [(0, 1), (1, 1), (2, 1)],
                },
                Row {
                    cell_indices: [(0, 2), (1, 2), (2, 2)],
                },
                Row {
                    cell_indices: [(0, 0), (1, 1), (2, 2)],
                },
                Row {
                    cell_indices: [(0, 2), (1, 1), (2, 0)],
                },
            ];
            Grid {
                cells: new_cells,
                rows,
                next_player: PlayerSymbol::O,
            }
        }

        pub fn is_tie(&self) -> bool {
            for cell in &self.cells {
                for c in cell {
                    if c.current_player_symbol == PlayerSymbol::EMPTY {
                        return false;
                    }
                }
            }
            return true;
        }
    }

    pub trait Draw {
        fn draw(&self);
    }
}
