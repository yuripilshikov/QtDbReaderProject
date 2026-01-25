# Overall

Reader for database of C++ standards.
It is strongly recommended to use database **cppref_db.sqlite**.

- db -> open database;
- All tabs will be populated with data;
- Selection of one row will show corresponding data (description and snippet/header example if exists);
- On first two tabs data is shown only for selected standard.

## Main window

- Handles database connection;
- Contaier for model widgets;
- Container for graphic widgets (TODO).

## Query model tab

- Uses MySqlQueryModel as model, child of QSquQueryModel (overloaded data() method);
- Delegate is default.

## Table model tab

- Uses MySqlTableModel as model, child of QSqlTableModel (overloaded data() method);
- Had to use TableView instead of ListView.

## Relational model tab

- Uses custom delegate (MySqlRelationDelegate) (overloaded paint() method).

## Statistics

- Just to have some fun with Qt Charts.

