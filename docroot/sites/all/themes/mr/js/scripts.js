(function ($) {
    Drupal.behaviors.customScriptsCetelem = {
        attach: function (context, settings) {

            $(window).resize(function () {
                set_responsive_images();
                resize_parallax_images();
            });


            var show = getUrlParameter('show');

            if ($('.galleria').length > 0) {
                Galleria.loadTheme('/sites/all/themes/sftw/themes/classic/galleria.classic.min.js');
                Galleria.run('.galleria', {
                    responsive: true,
                    thumbnails: false,
                    show: show,
                    debug: false,
                    extend: function (options) {
                        var gallery = this;
                        this.bind('image', function (e) {
                            var curr = gallery.getData(gallery.getIndex());
                            var currOrig = curr.original;
                            var altTxt = $(currOrig).attr('sources');
                            var currClass = $(currOrig).attr('class');

                            $(e.imageTarget).attr('sources', altTxt);
                            $(e.imageTarget).addClass(currClass);
                        });
                    }
                });
                Galleria.ready(function () {
                    set_responsive_images();
                });
            }

            resize_parallax_images();
            set_responsive_images();

            function resize_parallax_images() {
                $(".parallax-bg").each(function () {
                    var height = $(this).parent().width() / 2000 * 1102;
                    var image_source = jQuery(this).attr('src');
                    $(this).parent().css("background-image", 'url(' + image_source + ')');
                    $(this).parent().css("height", height);
                    if ($(this).parent().width() < 768) {
                        $(this).parent().find('.center-wrapper').css("height", height);
                    } else {
                        $(this).parent().find('.center-wrapper').css("height", '100vh');
                    }
                });
            }

            function set_responsive_images() {
                var width = $(window).width();
                var index = 3;
                if (width <= 480) {
                    index = 0;
                } else if (width <= 768) {
                    index = 1;
                } else if (width <= 992) {
                    index = 2;
                }

                $('.photo-album-image').each(function () {
                    var sourcesString = $(this).attr('sources');
                    var sources = sourcesString.split(';');
                    $(this).attr('src', sources[index]);

                });
            }


            function getUrlParameter(sParam) {
                var sPageURL = window.location.search.substring(1);
                var sURLVariables = sPageURL.split('&');
                for (var i = 0; i < sURLVariables.length; i++) {
                    var sParameterName = sURLVariables[i].split('=');
                    if (sParameterName[0] == sParam) {
                        return sParameterName[1];
                    }
                }
            }
        }
    };

}(jQuery));