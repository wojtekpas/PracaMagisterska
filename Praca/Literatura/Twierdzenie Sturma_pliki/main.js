jQuery(function($) {
	/**
	 * Remove .active class from the active item whem mouse is over the list
	 */
	$(".nav-list").hover(function() {
		var $activeElement = $(this).find("> .active");
		$(this).data("active-element", $activeElement);
		
		$activeElement.removeClass("active");
	}, function() {
		$(this).data("active-element").addClass("active");
	});
	
	/*
	 *  Inputs watermarks
	 */
	$("#search-form input[type=text]").each(function() {
		var $label = $("label[for=" + this.getAttribute("id") + "]").hide();
		var text   = $label.text().toUpperCase();

		$(this).addClass("watermark").focus(function() {
			if (text == $(this).val()) {
				$(this).val("");
			}
		}).blur(function() {
			if ("" == $(this).val()) {
				$(this).val(text);
			}
		}).blur();
	});
	
	/**
	 * Allows to expand and collapse boxes
	 */
	$("section.expandable, ul.expandable > li").each(function() {
		var $header  = $('header:eq(0)', this).addClass("expanded").css({ cursor: "pointer" });
		var $content = $('.content-wrapper:eq(0)',this).hide(); 
                	
		$header.find("h1, h2, h3, h4, h5, h6").eq(0).after($("<div class='marker' />"));
		
		$header.toggle(function() {
			$content.slideUp("fast", function() {
				$header.toggleClass("collapsed expanded");
		});
		}, function() {
			$header.toggleClass("collapsed expanded");
			$content.slideDown(0,
			function(){
			  var highslide= $("#highslide-wrapper");
			  if (highslide.length > 0){
			  parent.window.hs.getExpander().reflow();
			  };
			  /* parent.window.hs.getExpander().reflow(); */
			  })
		}).click();
               if ("true" == this.getAttribute("data-expanded")){$header.click();};
              /*$("section.expandable:not([data-expanded]), ul.expandable > li[data-expanded*='true']").click();*/
	});

	$(".story-info-expandable").each(function() {
		var $header  = $('time:eq(0)',this).addClass("expanded").css({ cursor: "pointer" });
		
		
		var $content = $('[id|="info-content"]',this); 
                	
		// $header.before($("<div style='float:right;margin-left:5px;' class='marker' />"));
		$header.append($("<span style='float:right;margin-left:5px;' class='marker' />"));
		
		
		$header.toggle(function() {
			$content.slideUp("fast", function() {
				$header.toggleClass("collapsed expanded");
		});
		}, function() {
			$header.toggleClass("collapsed expanded");
			$content.slideDown(50,
			function(){
			  var highslide= $("#highslide-wrapper");
			  if (highslide.length > 0){
			  parent.window.hs.getExpander().reflow();
			  };
			  /* parent.window.hs.getExpander().reflow(); */
			  })
		}).click();
            /*    if ("true" == this.getAttribute("data-expanded")){$header.click();};*/ 
              /*$("section.expandable:not([data-expanded]), ul.expandable > li[data-expanded*='true']").click();*/
	});

	$(".exercise-info-expandable").each(function() {
		var $content = $('[id|="info-content"]',this);
		if ($("body").hasClass('story')  &&  $content.find("li.s-v").length == 0){
                 return;
                };
		var $anchor  = $('.marker-anchor',this).addClass("expanded").css({ cursor: "pointer" });
		$anchor.append($('<div style="margin-left:5px;float:none;width:18px;display:inline-block;" class="marker" ></a>'));
		$anchor.toggle(function() {
			$content.slideUp("fast", function() {
				$anchor.toggleClass("collapsed expanded");
		});
		}, function() {
			$anchor.toggleClass("collapsed expanded");
			$content.slideDown(50,
			function(){
			  var highslide= $("#highslide-wrapper");
			  if (highslide.length > 0){
			  parent.window.hs.getExpander().reflow();
			  };
			  /* parent.window.hs.getExpander().reflow(); */
			  })
		}).click();
            /*    if ("true" == this.getAttribute("data-expanded")){$anchore.click();};*/ 
              /*$("section.expandable:not([data-expanded]), ul.expandable > li[data-expanded*='true']").click();*/
	});
	
	$(".articles-expandable").each(function() {
		var $articles = $('article',this).addClass("short");
		var $anchor  = $('.marker-anchor',this).addClass("collapsed").css({ cursor: "pointer" });
		$anchor.append($('<div style="margin-left:5px;float:none;width:18px;display:inline-block;" class="marker" ></a>'));
		$anchor.toggle(function() {
			$anchor.toggleClass("collapsed expanded");
			$articles.toggleClass("full short");
		}, function() {
			$anchor.toggleClass("collapsed expanded");
			$articles.toggleClass("full short");
		}).click();
	});

	
	$(".more-marker").append($('<div style="margin-left:5px;float:none;width:18px;display:inline-block;" class="marker" ></a>'));
        
        
/* eureka round  */
	$("div.eureka-list section.eureka:first").addClass("top-rounded");        
       $("div.eureka-list section.eureka:last").addClass("bottom-rounded");  

	/**
	 * Little triangles
	 */
	$(window).bind("resize", function() {
	    $(".triangle").remove();
	
	    $(".left-triangle, .right-triangle").each(function() {
			var $this = $(this);
			var $triangle = $("<div class='triangle' />");
			var dir = $this.hasClass("left-triangle") ? "left" : "right";
			var top = 0, left = 0;
			var backgroundX = 0;
			var backgroundY = dir == "left" ? 0 : -8;

			$.each("white crimson cadet-blue teal lavender-gray chamoisee".split(" "), function(i) {
				if ($this.hasClass(this)) {
					backgroundX = i * 8 * -1;
				}
			});

			top = $this.offset().top;
			if ($.browser.msie) {
			    top++;
			}

			left = $this.offset().left;
			if (dir == "left") {
			    left -= 8;
			} else {
			    left += $this.width();
			}

			$triangle.css("backgroundPosition", backgroundX + "px " + backgroundY + "px").css({ top: top, left: left });
			$this.css({ position: "relative" });
			$("body").append($triangle);
		 });
	}).trigger("resize");
	$(".sidebar,#cse,.expandable").bind("resize", function() {
	    $(".triangle").remove();
	
	    $(".left-triangle, .right-triangle").each(function() {
			var $this = $(this);
			var $triangle = $("<div class='triangle' />");
			var dir = $this.hasClass("left-triangle") ? "left" : "right";
			var top = 0, left = 0;
			var backgroundX = 0;
			var backgroundY = dir == "left" ? 0 : -8;

			$.each("white crimson cadet-blue teal lavender-gray chamoisee".split(" "), function(i) {
				if ($this.hasClass(this)) {
					backgroundX = i * 8 * -1;
				}
			});

			top = $this.offset().top;
			if ($.browser.msie) {
			    top++;
			}

			left = $this.offset().left;
			if (dir == "left") {
			    left -= 8;
			} else {
			    left += $this.width();
			}

			$triangle.css("backgroundPosition", backgroundX + "px " + backgroundY + "px").css({ top: top, left: left });
			$this.css({ position: "relative" });
			$("body").append($triangle);
		 });
	});
	 
	 
	 $("#send-error").attr('href', 'm' +'a'+ 'i'+'l' +'to:'+'deltami.edu.pl' + '@' + 'gmail' + "." +'com');
	 
	 /**
	  * Thumbnails zoom
	  
	$(".content-wrapper figure a:has(img)").click(function(e) {
		var $this	   = $(this);
		var $img		= $this.find("img");
		var $caption	= $this.parent().find("figcaption");
		var $frame	  = $("<div class='thumbnail-zoom'></div>");
		var imageOffset = $img.offset();
	
		$frame.css({ top: imageOffset.top, left: imageOffset.left });
		$frame.append($("<img />").attr("src", $img.attr("src")));
		
		if ($caption.size() > 0) {
			$frame.append($("<p />").html($caption.html()));
		}
		
		$("body").click(function() {
			$(".thumbnail-zoom").hide("normal");
		}).click().append($frame);
		
		$frame.show("normal");
	
		return false;
	}); */
});
