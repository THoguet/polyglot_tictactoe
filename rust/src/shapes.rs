pub mod shapes {
    use rust::{Cell_status, Coordinate};

    struct Cell {
        status: Cell_status,
        c: Coordinate,
    }

    struct Row {
        cells: [Cell; 3],
    }

    impl Shape for Row {
        fn is_win(&self) -> bool {
            let last_player = &self.cells[0].status;
            for c in &self.cells {
                let status = &c.status;
                if *last_player != *status {
                    return false;
                }
            }
            return true;
        }
        fn play(&self, c: Coordinate) {}
    }

    pub trait Shape {
        fn play(&self, c: Coordinate);
        fn is_win(&self) -> bool;
    }

    pub trait Draw {
        fn draw(&self);
    }
}
