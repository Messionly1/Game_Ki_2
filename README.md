# REVIEW
* Dự án làm game sử dụng ngôn ngữ C++ kết hợp SDL2.

# AUTHOR
	Phạm Vinh Trí - K69-ICS2 - 24021646.

# Flappybird
Technologies:
* C++
* SDL2 ...

# Cách cài đặt:
* Sử dụng CB và tải và cài đặt SDL, add file .dll 
* Cách chơi :
	1. Mở project và Run
	2. Run gameplay lan2.exe

# Nội dung:
- Mục tiêu là tránh va chạm với các ống hoặc mặt đất và ghi điểm bằng cách vượt qua các cặp ống.
- Game gồm Menu gồm Play,Setting,Quit,Rank.
	+ Setting: choose Music.
	+ Rank: 1-3
- Flappy Bird là một trò chơi đơn giản nhưng gây nghiện, trong đó người chơi điều khiển một chú chim nhỏ bay qua các khe hở giữa các ống     
  mà không để va chạm. Trò chơi kết thúc khi chim chạm vào ống hoặc mặt đất.
- Mỗi frame sẽ cập nhật tọa độ x,y cho player.Tọa độ y sẽ được tự + GRAVITY.(VelocityX+=GRAVITY)
- Click vào màn hình để player bay lên, bằng cách gán VelocityX = -const .
- Player sẽ được check tọa độ để xử lý va chạm với Pipe.
- Sau khi chạy hết màn,Pipe sẽ được quay lại và random 1 tọa độ Y trong khoảng cho trước.
- Pipe có đa dạng trạng thái:di chuyển,đứng yên,random SizePipes.
- Để có Moving Pipe, cài đặt GravityY cho Pipe.


# Asset  

- https://develion.itch.io/flappy-bird-unity-project

- Sử dụng chatGPT để vẽ menu,button...

- Ngoài ra tự kết nối các png bằng paint để tạo new asset

- Audio : music().wav : googleChrome

# Ý tưởng(UPDATE)

- Game DEMO của Giảng Viên.

- https://www.youtube.com/watch?v=YHH2101OFfI

- https://www.youtube.com/shorts/74s4Z7Fm_NE

Mức độ sử dụng AI: 35% (?): debug,plan,idea...

### Checklist

Texture

Background

Event chuột

Animation

Xử lý va chạm

Score 

Lưu điểm

Sound

Sound on off

Background music

Font

Menu

Status bar / Lives (mạng/máu...)

Các điểm nổi bật khác:

- Quản lí các đối tượng bằng vector

- Button hovering

- Camera scrolling

- Ranking

- Medal

- Hệ thống đếm điểm









