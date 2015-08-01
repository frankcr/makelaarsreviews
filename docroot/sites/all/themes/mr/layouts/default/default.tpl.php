<?php
/**
 * @file
 * Template for Cetelem.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display cetelem clearfix <?php !empty($class) ? print $class : ''; ?>" <?php !empty($css_id) ? print "id=\"$css_id\"" : ''; ?>>

  <div id="top_container">
    <?php print $content['contenttop']; ?>
  </div>

  <div id="content_container">
    <?php print $content['contentmain']; ?>
  </div>

  <div id="bottom_container">
    <?php print $content['contentbottom']; ?>
  </div>

</div>