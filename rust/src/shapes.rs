pub mod shapes {

    use rust::{Coordinate, PlayerSymbol};

    #[derive(Debug)]
    pub struct Cell {
        current_player_symbol: PlayerSymbol,
        coordinate: Coordinate,
    }

    #[derive(Debug)]
    pub struct Grid {
        cells: [[Cell; 3]; 3],
        rows: [Row; 8],
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
        fn play(&mut self, p: PlayerSymbol) {
            self.current_player_symbol = p;
        }
    }

    impl Draw for Grid {
        fn draw(&self) {
            for cell in &self.cells {
                print!("|");
                for c in cell {
                    if c.current_player_symbol == PlayerSymbol::EMPTY {
                        print!(" ");
                    } else {
                        print!("{:?}", c.current_player_symbol);
                    }
                    print!("|");
                }
                println!();
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

        pub fn get_cell(&mut self, x: usize, y: usize) -> &mut Cell {
            &mut self.cells[x][y]
        }

        pub fn play(&mut self, c: Coordinate, player: PlayerSymbol) {
            if player == PlayerSymbol::EMPTY {
                return;
            }
            let cell = self.get_cell(c.get_x() as usize, c.get_y() as usize);
            cell.play(player);
        }

        pub fn new() -> Grid {
            let new_cells: [[Cell; 3]; 3] = [
                [
                    Cell {
                        current_player_symbol: PlayerSymbol::EMPTY,
                        coordinate: Coordinate::new(0, 0),
                    },
                    Cell {
                        current_player_symbol: PlayerSymbol::EMPTY,
                        coordinate: Coordinate::new(0, 1),
                    },
                    Cell {
                        current_player_symbol: PlayerSymbol::EMPTY,
                        coordinate: Coordinate::new(0, 2),
                    },
                ],
                [
                    Cell {
                        current_player_symbol: PlayerSymbol::EMPTY,
                        coordinate: Coordinate::new(1, 0),
                    },
                    Cell {
                        current_player_symbol: PlayerSymbol::EMPTY,
                        coordinate: Coordinate::new(1, 1),
                    },
                    Cell {
                        current_player_symbol: PlayerSymbol::EMPTY,
                        coordinate: Coordinate::new(1, 2),
                    },
                ],
                [
                    Cell {
                        current_player_symbol: PlayerSymbol::EMPTY,
                        coordinate: Coordinate::new(2, 0),
                    },
                    Cell {
                        current_player_symbol: PlayerSymbol::EMPTY,
                        coordinate: Coordinate::new(2, 1),
                    },
                    Cell {
                        current_player_symbol: PlayerSymbol::EMPTY,
                        coordinate: Coordinate::new(2, 2),
                    },
                ],
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
            }
        }
    }

    pub trait Draw {
        fn draw(&self);
    }
}
