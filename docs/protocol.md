
# Table of Content

- [Table of Content](#table-of-content)
- [Format](#format)
- [Commands](#commands)
    - [Map](#map)
    - [Raw Map](#raw-map)
    - [Fly Status](#fly-status)
    - [Game Result](#game-result)
- [Response Types](#response-types)
  - [`ID` - Responses (🕹️ Client)](#id---responses-️-client)
  - [`MAP` - Responses (🕹️ Client)](#map---responses-️-client)
  - [`READY` - Responses (🖥️ Server)](#ready---responses-️-server)
  - [`LOBBY` - Responses (🕹️ Client)](#lobby---responses-️-client)
  - [`START` - Responses (🕹️ Client)](#start---responses-️-client)
  - [`PLAYER` - Responses (🕹️ Client)](#player---responses-️-client)
  - [`FLY` - Responses (🖥️ Server)](#fly---responses-️-server)
  - [`COIN` - Responses (🕹️ Client)](#coin---responses-️-client)
  - [`END` - Responses (🕹️ Client)](#end---responses-️-client)
- [Timeline Example](#timeline-example)

# Format

Since the Jetpack Communication Protocol is based on [TCP](https://en.wikipedia.org/wiki/Transmission_Control_Protocol), the **Client** and the **Server** will communicate using [commands](#commands) and [responses](#response-types).

The format of a command will be made up of the **command name** and then the **arguments data**:

```
<command> <data>
```

For example, for the **Server** to send new informations about a Player to a **Client**, it would be:

```
PLAYER 1 21.0 3.1 4 1
```

This command would mean that the **Server** is sending the new informations of a Player to a **Client**.

The updated informations are concerning the **Player 1**, he is now at the coordinates `x=21.0 y=3.1`, he now has **4 coins**, and he is flying.

The **command name** is [case insensitive](https://en.wikipedia.org/wiki/Case_sensitivity)

The command is ending with a Carriage Return Line Feed ([CRLF](https://fr.wikipedia.org/wiki/Carriage_Return_Line_Feed))


The response is a little different, it will only contain a [**response code**](#response-types) and an optional **message**:

```
<code> [<message>]
```

The **message** will only be specified in case of an error. It can contain spaces, it will indicate the outcome of the command processing.

For example if the command `MAP 61 _______e…` is sent, and the client parsed it successfully, the response would like:

```
OK
```

And in case of a parsing error, like an unrecognized character, the response would be:

```
ERROR Character not recognized: 'p'
```

The **response code** is [case insensitive](https://en.wikipedia.org/wiki/Case_sensitivity)

The response is ending with a Carriage Return Line Feed ([CRLF](https://fr.wikipedia.org/wiki/Carriage_Return_Line_Feed))

# Commands

| **Command** | **Args** | **Meaning** | **Sent by** |
| --- | --- | --- | --- |
| **`ID`** | `<player_id>` | Sends to the Client its **ID**<br>`<player_id> uint`: The **ID** of the Client chosen by the Server | 🖥️ Server |
| **`MAP`** | `<length> <raw_map>` | Sends the **map** to the Client<br>`<length> uint`: Length of the **map** (width)<br>`<raw_map> raw_map`: [Raw map](#raw-map) of the **map** | 🖥️ Server |
| **`READY`** | *None* | Sends to the Server that the Client is **ready** | 🕹️ Client |
| **`LOBBY`** | `<players>` `<ready_players>` | Sends to the Client the lobby informations<br>`<players>`: Comma-separated **IDs** of the players in the lobby<br>`<ready_players>`: Comma-separated **IDs** of the players in the lobby that are ready | 🖥️ Server |
| **`START`** | *None* | Sends to the Client that the **game starts**  | 🖥️ Server |
| **`PLAYER`**  | `<player_id> <pos_x> <pos_y> <score> <fly_status>` | Sends to the Client the updates of a **player**<br>`<player_id> uint`: The **ID** of the **player**<br>`<pos_x> ufloat`: The `x` coordinate of the **player**<br>`<pos_y> ufloat`: The `y` coordinate of the **player**<br>`<score> uint`: The number of coins the **player** has<br>`<fly_status> fly_status`: The [Fly Status](#fly-status) of the **player** | 🖥️ Server |
| **`FLY`**  | `<fly_status>` | Sends to the Server that the Client want to change **Fly Status**<br>`<fly_status> fly_status`: [Fly Status](#fly-status) | 🕹️ Client |
| **`COIN`** | `<player_id> <pos_x> <pos_y>` | Sends to the Client that a player just took a **coin**<br>`<player_id> uint`: The player that got the **coin**<br>`<pos_x> uint`: The `x` coordinate of the **coin**<br>`<pos_y> uint`: The `y` coordinate of the **coin** | 🖥️ Server |
| **`END`** | `<game_result>` | Sends to the Client that the **game** has ended<br>`<game_result> game_result`: [Game Result](#game-result) | 🖥️ Server |

### Map

The syntax of a **map** is not very hard, every **character** represent an object in the game.
The **map** is visually representing the in-game map. So every lines are separated by a new line (`\n`)

Here is the **map** objects available:

- `_`: Empty cell
- `c`: Coin
- `e`: Electric cell

The **map** should have a static height of **10**, but the length of the map is **variable**.

Here is an example of a **map** file:

```
____________________________e__________________________________________________________________
____________________________e______cccccc______________________________________________________
____________________________e_____ccccccc________________________eeeeeeeeeeee__________________
____________________________e____cc____________________________________________________________
____________________________e___cc______e_________________________cccc_________________________
_______________________________cc_______e_________________________cccc_________________________
_________________________ccccccc________e______________________________________________________
_________________________cccccc_________e_________________eeeeeeeeeeeee________________________
________________________________________e______________________________________________________
________________________________________e______________________________________________________
```

### Raw Map

`raw_map` format is used to pass in a **command** a map

The way to convert a map into a **raw map** is easy, just remove the **new lines** (`\n`)

### Fly Status

`fly_status` is a boolean representing whether the Client want to **fly** or not

`0`: Means the Client want to stop **flying**

`1`: Means the Client want to start **flying**

### Game Result

`game_result` is an enum representing the outcome of a game

`0`: Means nobody won the game, **draw**

`x`: Means the player with the **ID** `x` **won** the game

# Response Types

| **Type** | **Meaning** |
| --- | --- |
| **`OK`** | Means that the **Client/Server** correctly parsed and interpreted the information sent in the Command and the information is logic with the current game |
| **`ERROR`** | Means that the **Client/Server** catched an error while parsing or interpreting the information sent in the Command or the information is conflicting with the current game, means that there is a logic error.  |

## `ID` - Responses (🕹️ Client)

| **Type** | **Message** | **Meaning** |
| --- | --- | --- |
| **`OK`** | *None* | The **Client** parsed and interpreted correctly the **ID** |
| **`ERROR`** | `Invalid ID`  | The **Client** catched an error while parsing or interpreting the **ID** |

## `MAP` - Responses (🕹️ Client)

| **Type** | **Message** | **Meaning** |
| --- | --- | --- |
| **`OK`** | *None* | The **Client** correctly parsed and interpreted the **Length** and the **Map** |
| **`ERROR`** | `Character not recognized: ‘<char>'` | The **Map** includes an unknown character that is not part of the [objects list](#map) |
| **`ERROR`** | `Map length mismatch` | The **Map** received does not match the **Length** provided |

## `READY` - Responses (🖥️ Server)

| **Type** | **Message** | **Meaning** |
| --- | --- | --- |
| **`OK`** | *None* | The **Server** correctly registered that **Client** is ready |
| **`ERROR`** | `Already ready` | The **Server** already registered that the **Client** is ready |
| **`ERROR`** | `Not accepting ready now` | The **Server** is not waiting for clients, means that the game already started or is already finished |

## `LOBBY` - Responses (🕹️ Client)

| **Type** | **Message** | **Meaning** |
| --- | --- | --- |
| **`OK`** | *None* | The **Client** successfully updated the lobby informations |
| **`ERROR`** | `Invalid list of players` | The **Client** catched an error while parsing or interpreting the **list of players** |
| **`ERROR`** | `Invalid list of ready players` | The **Client** catched an error while parsing or interpreting the **list of players** that are **ready** |
| **`ERROR`** | `Lobby command unexpected` | The **Client** is currently not in a lobby |

## `START` - Responses (🕹️ Client)

| **Type** | **Message** | **Meaning** |
| --- | --- | --- |
| **`OK`** | *None* | The **Client** successfully started the **Game** |
| **`ERROR`** | `Start command unexpected` | The **Client** isn't ready to start the **Game** |

## `PLAYER` - Responses (🕹️ Client)

| **Type** | **Message** | **Meaning** |
| --- | --- | --- |
| **`OK`** | *None* | The **Client** correctly parsed and interpreted the updated **player data** |
| **`ERROR`** | `Invalid number of data` | The number **datas** received isn't the one expected |
| **`ERROR`** | `Invalid player ID` | The **Player ID** received is not a number |
| **`ERROR`** | `Unknown player ID` | The **Player ID** received is not associated with a **Player** |
| **`ERROR`** | `Invalid x coordinate` | The **Client** catched an error while parsing or interpreting the **x coordinate** |
| **`ERROR`** | `Invalid y coordinate` | The **Client** catched an error while parsing or interpreting the **y coordinate** |
| **`ERROR`** | `Invalid score` | The **Client** catched an error while parsing or interpreting the **score** |
| **`ERROR`** | `Invalid fly status` | The **Client** catched an error while parsing or interpreting the [fly_status](#fly-status) |

## `FLY` - Responses (🖥️ Server)

| **Type** | **Message** | **Meaning** |
| --- | --- | --- |
| **`OK`** | *None* | The **Server** correctly parsed, interpreted and updated the [Fly Status](#fly-status) of the **Player** |
| **`ERROR`** | `Invalid fly status` | The **Server** catched an error while parsing or interpreting the [fly_status](#fly-status) |
| **`ERROR`** | `Command not allowed` | The command is used at a time when the **game** is not **running** |

## `COIN` - Responses (🕹️ Client)

| **Type** | **Message** | **Meaning** |
| --- | --- | --- |
| **`OK`** | *None* | The **Client** correctly parsed, interpreted and updated the **Coin** of the **Player** |
| **`ERROR`** | `Invalid number of data` | The number **datas** received isn't the one expected |
| **`ERROR`** | `Invalid player ID` | The **Player ID** received is not a number |
| **`ERROR`** | `Unknown player ID` | The **Player ID** received is not associated with a **Player** |
| **`ERROR`** | `Invalid x coordinate` | The **Client** catched an error while parsing or interpreting the **x coordinate** |
| **`ERROR`** | `Invalid y coordinate` | The **Client** catched an error while parsing or interpreting the **y coordinate** |

## `END` - Responses (🕹️ Client)

| **Type** | **Message** | **Meaning** |
| --- | --- | --- |
| **`OK`** | *None* | The **Client** correctly parsed, interpreted and stopped the **Game** |
| **`ERROR`** | `Invalid game result` | The **Client** catched an error while parsing or interpreting the [game_result](#game-result) |

# Timeline Example

Here is an example of the interaction between **1 Server** and **1 Client**:

```cpp
# Client connecting to Server...
# Initialization
[SERVER] "ID 1"
[CLIENT] "OK"
[SERVER] "MAP 95 _________..."
[CLIENT] "OK"
[SERVER] "LOBBY 1,2 1"
[CLIENT] "OK"
[CLIENT] "READY"
[SERVER] "OK"
# Game
[SERVER] "START"
[CLIENT] "OK"
[SERVER] "PLAYER 1 0.0 5.0 0 0"
[CLIENT] "OK"
[SERVER] "PLAYER 1 1.0 4.9 0 0"
[CLIENT] "OK"
[SERVER] "PLAYER 1 2.0 4.8 0 0"
[CLIENT] "OK"
[CLIENT] "FLY 1"
[SERVER] "OK"
[SERVER] "PLAYER 1 3.0 4.9 0 1"
[CLIENT] "OK"
[SERVER] "PLAYER 1 4.0 5.0 0 1"
[CLIENT] "OK"
[SERVER] "PLAYER 1 5.0 5.1 0 1"
[CLIENT] "OK"
[SERVER] "PLAYER 1 6.0 5.2 0 1"
[CLIENT] "OK"
[SERVER] "COIN 1 7 6"
[CLIENT] "OK"
[CLIENT] "FLY 0"
[SERVER] "OK"
[SERVER] "PLAYER 1 7.0 5.2 1 0"
[CLIENT] "OK"
# Ending
[SERVER] "END 1"
[CLIENT] "OK"
```
