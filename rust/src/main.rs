use std::io;

use rust::shapes::{Draw, Grid};
use rust::Coordinate;

fn main() {
    let mut grid = Grid::new();
    loop {
        draw_grid(&grid);
        let player = grid.next();
        println!("Au tour du joueur {:?}\n", player);
        let mut player_played = false;
        while !player_played {
            match ask_player() {
                Ok(coo) => {
                    player_played = grid.play(coo, player);
                    if !player_played {
                        println!("Vous ne pouvez pas jouer sur cette case.")
                    }
                }
                Err(err) => println!("{:?}", err),
            }
        }
        if grid.is_win() {
            draw_grid(&grid);
            println!("Le joueur {:?}, a gagné !!!", player);
            return;
        } else if grid.is_tie() {
            draw_grid(&grid);
            println!("Egalité ...");
            return;
        }
    }
}

fn draw_grid(grid: &Grid) {
    println!("{:?}", grid.draw());
}

fn ask_one_char(message: String) -> Result<char, &'static str> {
    println!("{:?}", message);
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    let size = buffer.chars().count();
    if size != 2 {
        return Err("invalid value");
    } else {
        Ok(buffer.chars().next().unwrap())
    }
}

fn ask_player() -> Result<Coordinate, &'static str> {
    let message = format!("Saisir x: ");
    let chara = ask_one_char(message)?;
    let x = char::to_digit(chara, 10).expect("value is not a number");
    let message = format!("Saisir y: ");
    let chara = ask_one_char(message)?;
    let y = char::to_digit(chara, 10).expect("value is not a number");
    Ok(Coordinate::new(x as u8, y as u8))
}
