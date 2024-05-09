import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
TextField {
    id: root
    Item {
        id: convert
        function toMiliseconds(h = 0, m = 0, s = 0, ms = 0) {
            return h * 3600000  + m * 60000 + s * 1000 + ms
        }
        function msToStr(mil) {
            var hours = Math.floor(mil / 3600000)
            var mins = Math.floor(mil % 3600000 / 60000)
            var s = mil % 3600000 % 60000 / 1000
            return hours + "h " + (mins<10?("0"+mins):mins + "m")
        }
    }
    function setTotalMs(ms)
    {
        root.text = convert.toMiliseconds(ms);
    }

    // property var minuts
    // property var hours
    property int totalMs
    onTotalMsChanged:
    {
        var strMs = convert.msToStr(totalMs);
        if(displayText != strMs)
        {text =strMs}

    }
    inputMask: "0\\h 00m;0"
    text: "0h 00m"
    onFocusChanged:
    {
        var minuts = displayText[3] + displayText[4] ; var hours =displayText[0];
        var ms = convert.toMiliseconds(hours,minuts)
        if(totalMs != ms)
           {totalMs = ms}
    }
}
