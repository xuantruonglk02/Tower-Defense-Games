- Nội dung chính của game: sử dụng các tháp phòng thủ, sắp xếp chúng lên màn hình để tiêu diệt quân địch kéo đến căn cứ

- cách chơi:
    - sử dụng thao tác kéo-thả chuột để đặt các tháp phòng thủ vào vị trí
    - có 4 loại súng và 2 loại tháp hỗ trợ
    - súng: súng máy, súng 2 nòng, súng laze, súng tên lửa
    - tháp hỗ trợ: tăng sát thương và tăng tầm bắn
    - có thể nâng cấp súng
    - game sẽ thua khi căn cứ hết máu, thắng khi tiêu diệt toàn bộ quái và căn cứ vẫn còn máu
    - có các wave, có 15s để chuẩn bị khi chuyển sang wave khác. có thể nhấn "NEXT" để chuyển ngay lập tức

- game bao gồm các class:
    - game: logic chính: các hàm chuyển hướng, gọi quái, thêm các tháp phòng thủ, xử lí bắn đạn, xử lí đạn bắn vào quái, bắn ra ngoài, sắp xếp quái theo thứ tự gần căn cứ nhất, vẽ game, xóa dữ liệu game cho lượt chơi sau.
    - menu: gồm các hàm kiểm tra việc: chọn map, bắt đầu chơi, menu cài đặt, thoát game.
    - sound: quản lí âm thanh game. có các hàm bật, tắt âm thanh.
    - gameTexture: quản lí texture của toàn bộ game để tái sử dụng.
    - map: đọc dữ liệu map từ file, tạo bản đồ đường đi của quái, tạo bản đồ vật cản trên map.
    - base: game kết thúc khi máu của base về 0.
    - wave: đọc dữ liệu về loại, số lượng quái từ file, lưu lại để gọi quái.
    - control_board: gồm bảng chọn tháp, hiển thị tiền, thời gian, thông tin từng loại tháp, có nút tạm dừng, tua nhanh thời gian chờ
    - gun: quản lí các loại súng về: vị trí, sát thương, tốc độ bắn, phạm vi bắn.
    - supporter: quản lí các loại tháp hỗ trợ về: vị trí, lượng sát thương hay tầm bắn mà súng được buff thêm.
    - bullet: xử lí việc di chuyển của viên đạn. (định hướng đường đạn với loại đạn tên lửa)
    - enemy: nhận dữ liệu đường đi từ map, điều khiển quái đi theo đường đi. thêm cả máu, sát thương gây ra cho căn cứ.
- file config.h: lưu thông số game
- file utils: chứa hàm khởi tạo và thoát sdl

- ban đầu vào game hiển thị bảng chọn menu, khi ấn "play" gọi hàm play bắt đầu chơi, chơi xong xóa dữ liệu rồi trở lại hàm menu chờ thao tác tiếp.

- game sử dụng các hàm load ảnh, load chữ từ trang lazyfoo
- game tham khảo đồ họa và lối chơi tại " http://www.trochoiviet.com/phong-thu-vung-bien/game.html "
- file âm thanh từ game soul knight, youtube.com, mixkit.co, soundsnap.com

- link video demo: " https://youtu.be/qvo4eX0AnXw "

- điểm tự chấm: 9

- phiên bản sau phát triển thêm:
    - thêm map
    - thêm loại quái mới
    - thêm súng với hiệu ứng mới
    - có thể lưu lại game đang chơi
