<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <title>Matrix Love</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        body, html {
            width: 100%;
            height: 100%;
            overflow: hidden;
            background-color: #000;
            font-family: 'Courier New', Courier, monospace;
        }
        canvas {
            display: block;
            position: absolute;
            top: 0;
            left: 0;
            z-index: 1;
        }
        #container {
            position: absolute;
            width: 100%;
            height: 100%;
            display: flex;
            justify-content: center;
            align-items: center;
            z-index: 2;
            color: #fff;
            text-shadow: 0 0 10px #ff69b4, 0 0 20px #ff69b4;
            text-align: center;
            padding: 20px;
        }
        #countdown {
            font-size: 8rem;
            font-weight: bold;
            transition: all 0.3s ease;
        }
        #message {
            font-size: 3.5rem;
            font-weight: bold;
            display: none;
            line-height: 1.4;
        }
        /* Gợi ý xoay ngang màn hình nếu là điện thoại dọc */
        #rotate-hint {
            display: none;
            position: fixed;
            top: 0; left: 0; width: 100%; height: 100%;
            background: #000; z-index: 999;
            color: #fff; justify-content: center; align-items: center;
            font-size: 1.5rem; text-align: center; padding: 20px;
        }
        @media (orientation: portrait) {
            #rotate-hint { display: flex; }
        }
    </style>
</head>
<body>

    <div id="rotate-hint">🔄 Vui lòng xoay ngang thiết bị của bạn</div>

    <canvas id="matrix"></canvas>
    
    <div id="container">
        <div id="countdown">3</div>
        <div id="message"></div>
    </div>

    <script>
        // --- 1. HIỆU ỨNG MƯA MA TRẬN (MATRIX RAIN) ---
        const canvas = document.getElementById('matrix');
        const ctx = canvas.getContext('2d');

        function resizeCanvas() {
            canvas.width = window.innerWidth;
            canvas.height = window.innerHeight;
        }
        resizeCanvas();
        window.addEventListener('resize', resizeCanvas);

        // Chữ cái để chạy hiệu ứng (Dùng bảng chữ cái Latinh/Ký tự lạ cho giống phim Matrix)
        const katakana = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$+-*/=<>!:";
        const alphabet = katakana.split("");

        const fontSize = 16;
        let columns = canvas.width / fontSize;
        let rainDrops = Array(Math.floor(columns)).fill(1);

        window.addEventListener('resize', () => {
            columns = canvas.width / fontSize;
            rainDrops = Array(Math.floor(columns)).fill(1);
        });

        function drawMatrix() {
            // Tạo hiệu ứng mờ dần bằng cách phủ một lớp đen trong suốt nhẹ
            ctx.fillStyle = 'rgba(0, 0, 0, 0.05)';
            ctx.fillRect(0, 0, canvas.width, canvas.height);

            // Màu chữ mưa rơi hồng tím giống trong video 1000048531.mp4
            ctx.fillStyle = '#cc55aa'; 
            ctx.font = fontSize + 'px monospace';

            for (let i = 0; i < rainDrops.length; i++) {
                const text = alphabet[Math.floor(Math.random() * alphabet.length)];
                ctx.fillText(text, i * fontSize, rainDrops[i] * fontSize);

                if (rainDrops[i] * fontSize > canvas.height && Math.random() > 0.975) {
                    rainDrops[i] = 0;
                }
                rainDrops[i]++;
            }
        }
        setInterval(drawMatrix, 30);


        // --- 2. HIỆU ỨNG CHẠY CHỮ TỎ TÌNH ---
        const countdownEl = document.getElementById('countdown');
        const messageEl = document.getElementById('message');

        // Danh sách các câu sẽ hiện lần lượt (Có thể sửa tùy ý)
        const phrases = [
            "Em đồng ý",
            "Làm người yêu",
            "Anh nhé 🤍",
            "Anh Yêu Em",
            "💟"
        ];

        let count = 3;
        
        // Đếm ngược 3, 2, 1
        const countdownTimer = setInterval(() => {
            count--;
            if (count > 0) {
                countdownEl.innerText = count;
            } else {
                clearInterval(countdownTimer);
                countdownEl.style.display = 'none';
                startTextAnimation();
            }
        }, 1000);

        // Chạy lần lượt các câu chữ
        function startTextAnimation() {
            messageEl.style.display = 'block';
            let currentPhraseIndex = 0;

            function showNextPhrase() {
                if (currentPhraseIndex < phrases.length) {
                    messageEl.innerText = phrases[currentPhraseIndex];
                    currentPhraseIndex++;
                    // Đổi câu sau mỗi 2 giây
                    setTimeout(showNextPhrase, 2000); 
                }
            }
            showNextPhrase();
        }
    </script>
</body>
</html>
