<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
        <title>맥도날드 동작구</title>
        <link rel="preconnect" href="https://fonts.gstatic.com">
        <link href="https://fonts.googleapis.com/css2?family=Black+Han+Sans&family=Nanum+Gothic&display=swap" rel="stylesheet">
        <style>
            .title>p{
                font-family: 'Black Han Sans', sans-serif;
                font-size : 50px;
                margin : 10px 0;
            }
            .data{
                font-family: 'Nanum Gothic', sans-serif;
            }
            .saleData{
                font-family: 'Nanum Gothic', sans-serif;
                margin : 15px 0 30px 0;
            }
            .link{
                margin : 25px 0;
            }
            .link > a{
                font-family:  'Black Han Sans', sans-serif;
                font-size : 30px; 
                text-decoration: none;
                color : cadetblue;
            }
            table{
                border-collapse: collapse;
            }
            table, td, th{
                border: solid 3px orangered;
            }
            th {
                background-color : orange;
                color : white;
            }
            .data{
                display : flex;
                flex-direction : row;
                justify-content : center;
            }
            .data > .storeData, .itemData{
                margin : 10px;
            }
        </style>
    </head>
    <body>
        <center>
            <div class="title">
                <p style= "color:cadetblue; display :inline-block;">동작구</p>
                <p style= "color:orangered; display : inline-block;">맥도날드</p>
                <p style= "display : inline-block;">주문현황</p>
            </div>
            <hr>
            <section class="data">
                <div class ="storeData">
                    <p style= "color:orangered; font-family: 'Black Han Sans', sans-serif; font-size : 30px; margin : 5px 0 10px 0;">점포 정보</p>
                    <?php
                        $conn=mysqli_connect('localhost','root','111114', 'finalproject');
                        if(!$conn){
                            die("MySQL connect error : ".mysql_error());
                        }

                        $result=mysqli_query($conn, "(select * from store left join storephone on sName=pName)union(select * from store right join storephone on sName=pName);");
                        echo "<table border='1'><tr><th>번호</th><th>점포명</th><th>주소</th><th>전화번호</th></tr>";
                        while($row=mysqli_fetch_array($result)){
                            echo "<tr>";
                            echo "<td>".$row['sNum']."</td>"; 
                            echo "<td>".$row['sName']."</td>"; 
                            echo "<td>".$row['address']."</td>";
                            echo "<td>".$row['phone']."</td>"; 
                            echo "</tr>";
                        }
                        echo "</table>";
                        mysqli_free_result($result);
                        mysqli_close($conn);
                    ?>
                </div>
                <div class ="itemData">
                    <p style= "color:orangered; font-family: 'Black Han Sans', sans-serif; font-size : 30px; margin : 5px 0 10px 0;">메뉴 정보</p>
                    <?php
                        $conn=mysqli_connect('localhost','root','111114', 'finalproject');
                        $result=mysqli_query($conn, "select * from item;");
                        echo "<table border='1'><tr><th>번호</th><th>메뉴명</th><th>가격</th></tr>";
                        while($row=mysqli_fetch_array($result)){
                            echo "<tr>";
                            echo "<td>".$row['iNum']."</td>"; 
                            echo "<td>".$row['iName']."</td>"; 
                            echo "<td>".$row['price']."</td>";
                            echo "</tr>";
                        }
                        echo "</table>";
                        mysqli_free_result($result);
                        mysqli_close($conn);
                    ?>
                </div>
            </section>
            <hr>
            <div class="saleData">
            <p style= "color:orangered; font-family: 'Black Han Sans', sans-serif; font-size : 30px; margin : 5px 0 10px 0;">주문 정보</p>
                <?php
                    $store= $_POST[store];
                    $menu=$_POST[menu_name];
                    $num=$_POST[quantity];
                    $time=$_POST[orderTime];
                    $aName=$_POST[menu_name1];
                    $aNum=$_POST[quantity1];
                    $phpdate = strtotime( $time );
                    $time = date( 'Y-m-d H:i:s', $phpdate );

                    $conn=mysqli_connect('localhost','root','111114', 'finalproject');

                    $sql="INSERT INTO sale(sName, iName, num, date) VALUES ('$store', '$menu','$num', '$time')";
                    
                   
                    $addsql="INSERT INTO addmenu(aName, aNum) VALUES ('$aName', '$aNum')";
                    
                    $result=mysqli_query($conn, $sql);
                    $result1=mysqli_query($conn, $addsql);
                    $result=mysqli_query($conn, "(select * from sale left join addmenu on count=aCount)union(select * from sale right join addmenu on count=aCount);");
                    echo "<table border='1'><tr><th>주문번호</th><th>점포명</th><th>메뉴명</th><th>수량</th><th>메뉴명2</th><th>수량</th><th>시간</th></tr>";
                    while($row=mysqli_fetch_array($result)){
                        echo "<tr>";
                        echo "<td>".$row['count']."</td>"; 
                        echo "<td>".$row['sName']."</td>"; 
                        echo "<td>".$row['iName']."</td>";
                        echo "<td>".$row['num']."</td>"; 
                        echo "<td>".$row['aName']."</td>"; 
                        echo "<td>".$row['aNum']."</td>"; 
                        echo "<td>".$row['date']."</td>"; 
                        echo "</tr>"; 
                    }  
                    echo "</table>";
                    mysqli_free_result($result);
                    mysqli_free_result($result1);
                    mysqli_close($conn);
                ?>
            </div>
            <hr>
            <section class="link">
                <a href="mcdonald.html">주문 추가하러 가기</a>
            </section>
     </center>
    </body>
</html>