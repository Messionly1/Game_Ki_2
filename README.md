# Flappybird
Technologies:
* C++
* SDL
# Cách cài đặt:
* Sử dụng CB và tải và cài đặt SDL, add file .dll 
* Cách 1: Mở project và Run
# Nội dung:
- Game chia thành các header cho Bird, Pipe, Render,Score...
- Mỗi frame sẽ cập nhật tọa độ x,y cho player.Tọa độ y sẽ được tự + GRAVITY.(VelocityX+=GRAVITY)
- Click vào màn hình để player bay lên, bằng cách gán VelocityX = -const .
- Player sẽ được check tọa độ để xử lý va chạm với Pipe.
- Sau khi chạy hết màn,Pipe sẽ được quay lại và random 1 tọa độ Y trong khoảng cho trước.
- Để có Moving Pipe, cài đặt GravityY cho Pipe.




