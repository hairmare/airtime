var __lc = {};
__lc.license = 1083735;

function setupLiveChat() {
    // this is where we pass custom variables to livechat;
    // only pass the client id assigned by WHMCS for now
    __lc.params = [
        { name: 'client_id', value: livechat_client_id },
        { name: 'plan_type', value: livechat_plan_type},
        { name: 'station_url', value: livechat_station_url}
    ];
    
    var lc = document.createElement('script'); lc.type = 'text/javascript'; lc.async = true;
    lc.src = ('https:' == document.location.protocol ? 'https://' : 'http://') + 'cdn.livechatinc.com/tracking.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(lc, s);
}

$(document).ready(function() {
    setupLiveChat();

    var lcLoadListener = setInterval(function() {
        var ifr = document.getElementById('livechat-compact-container');
        if (ifr) {
            LC_API.on_chat_state_changed = function(data) {
                // Hacky... select elements on pages that have different layouts separately
                $('body > .wrapper, #stream_form > div, #his-tabs').css('padding-bottom', (data.state == 'offline') ? 10 : 40);
            };
            clearInterval(lcLoadListener);
        }
    }, 100);
});