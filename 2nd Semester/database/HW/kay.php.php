<html>
    <title>사용자 등록 종료</title>
    <body>
        <center>
            <?php
	$id= $_POST[id];
 	$password=$_POST[password];
 	$name=$_POST[name];
	
                $conn=mysqli_connect('localhost','root','111114', 'test');
                $sql="insert into member(id, pass, name)
		values ('$id', '$password','$name')";
                $result=mysqli_query($conn, $sql);
                $result=mysqli_query($conn, "select * from member where id='$id'");

	   echo "사용자 등록 종료 - ".$id."<br><br>\n";
                while($row=mysqli_fetch_array($result)){
		echo "사용자 ID : ".$row['id']."<br>\n"; 
                    	echo "사용자명 : ".$row['name']."<br>\n"; 
                    	echo "비밀번호 : ".$row['pass']."<br>\n"; 
		}
                
                mysqli_free_result($result);
                mysqli_close($conn);
            ?>
	<a href="kay.html">[처음으로]</a>
        </center>
    </body>
</html>

