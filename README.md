# Flappybird
Technologies:
* C++
* SDL2
# Cách cài đặt:
* Sử dụng CB và tải và cài đặt SDL, add file .dll 
* Cách chơi :
	1. Mở project và Run
	2. Run gameplay lan2.exe
# Nội dung:
- Game chia thành các header cho Bird, Pipe, Render,Score...
- Game gồm Menu gồm Play,Setting,Quit,Rank.
	+ Setting: choose Music.
	+ Rank: 1-3
- Chim có 3 mạng để sống,nhưng chỉ khi chạm vào Pipe thì mới được hồi sinh,còn nếu rơi xuống đất chim sẽ chết ngay lập tức.
- Khi bắt đầu game,sẽ được random màu sắc của chim,có 3 màu:đỏ,xanh dương,vàng.
- Hệ thống on/off sound khi chơi game.
- Mỗi frame sẽ cập nhật tọa độ x,y cho player.Tọa độ y sẽ được tự + GRAVITY.(VelocityX+=GRAVITY)
- Click vào màn hình để player bay lên, bằng cách gán VelocityX = -const .
- Player sẽ được check tọa độ để xử lý va chạm với Pipe.
- Sau khi chạy hết màn,Pipe sẽ được quay lại và random 1 tọa độ Y trong khoảng cho trước.
- Pipe có đa dạng trạng thái:di chuyển,đứng yên,random SizePipes.
- Để có Moving Pipe, cài đặt GravityY cho Pipe.
- Khi chim chết,nếu điểm thuộc top 1-3 cao nhất sẽ được lưu vào bảng và xếp vào RANK.
- Nếu chim đạt được điểm cao>=điểm cao nhất thì chim sẽ nhận được 1 medal.
- Hệ thống điểm được setup chạy từ 1 -> CURRENT_POINT.






