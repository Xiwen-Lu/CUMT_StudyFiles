/**用于注册验证
 * 满足要求时弹出“注册成功”
 */
function validate(f)
{
	var name=f.ID.value;
	var flag=1;
	var RegName=/^[\w\d]*$/;
	if(!RegName.test(name))
	{
		alert("用户名只能是数字和字母");
		f.ID.focus();
		f.ID.select();
		flag=-1;
	}
	var pass=f.password.value;
	if(pass.length<6)
	{
		alert("密码必须大于6位");
		flag=-1;
	}
	if(flag==1)
	{
		location.href="./zhuceSucc.html";
	}
}

