'USBHID.dll需註冊，步驟如下:
'                 1. 將 USBHID.dll 檔案置於 [C:\windows\system32\] 資料夾中
'                 2. 在 [附屬應用程式 \ 命令提示字元] 按滑鼠右鍵 [以系統管理員身分執行]
'                 3. 輸入 cd\windows\system32  [Enter] (切換資料夾)
'                 4. 輸入 regsvr32 USBHID.dll  [Enter] (成功時會顯示[DllRedisterServer成功])
'                 5. 點選VB2010功能表 [ 專案 / 加入參考 / COM ] ，選擇 [ USBHID.DLL ] 按 [ 確定 ]
'
'表單中的形狀物件(OvalShape)由左至右放置16顆
'計時器的 Interval 設 1000， Enabled 設 True

Imports USBHID  '載入USBHID.dll
Imports Microsoft.VisualBasic.PowerPacks
Public Class Form1
    Dim usb As New HID
    Dim txBuf(8) As Byte

    Dim conn As Boolean
    '計時器，每秒執行一次

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Dim rxBuf(8) As Byte
        Label1.Text = "Current Time:" & TimeString '顯示系統時間
        conn = usb.OpenHIDDevice(&H1234, &H2468)  '板子連線(查詢HID/PID：人性化介面裝置/詳細資料/硬體識別碼)
        If conn Then
            Label2.Text = "ON"
            OvalShape2.FillColor = Color.Red
        Else
            Label2.Text = "OFF"
            OvalShape2.FillColor = Color.FromArgb(255, 192, 192)
        End If
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        txBuf(0) = 4 : txBuf(1) = 0 : usb.HIDSetReport(txBuf) 'LOGO 1
    End Sub
    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        txBuf(0) = 4 : txBuf(1) = 1 : usb.HIDSetReport(txBuf) 'LOGO 2
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        txBuf(0) = 5 : txBuf(1) = Val(sender.Text) : usb.HIDSetReport(txBuf)
    End Sub

    Private Sub Button11_Click(sender As Object, e As EventArgs) Handles Button11.Click
        txBuf(0) = 1 : usb.HIDSetReport(txBuf)
        Dim rxBuf() As Byte = usb.HidGetReport()
        If rxBuf(2) = 1 Then
            OvalShape1.FillColor = Color.Yellow
        Else
            OvalShape1.FillColor = Color.FromArgb(255, 255, 192)
        End If

    End Sub

    Private Sub Button12_Click(sender As Object, e As EventArgs) Handles Button12.Click
        Dim rxBuf() As Byte = usb.HidGetReport()
        TextBox2.Text = rxBuf(2)
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Private Sub Button1_Click_1(sender As Object, e As EventArgs) Handles Button1.Click
        Dim x As Integer
        x = TextBox1.Text
        Dim th, hu, ten, num As Integer

        th = x \ 1000
        hu = (x \ 100) Mod 10
        ten = (x \ 10) Mod 10
        num = x Mod 10
        txBuf(0) = 2
        txBuf(1) = th
        txBuf(2) = hu
        txBuf(3) = ten
        txBuf(4) = num
        usb.HIDSetReport(txBuf)
    End Sub

    Private Sub Button2_Click_1(sender As Object, e As EventArgs) Handles Button2.Click
        txBuf(0) = 3 : usb.HIDSetReport(txBuf)
    End Sub
End Class
