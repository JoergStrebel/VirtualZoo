package de.strebel;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.*;

/**
 * This class demonstrates how to load an Image from an external file
 * TODO: https://docs.oracle.com/javase/tutorial/2d/geometry/examples/ShapesDemo2D.java
 * TODO: https://docs.oracle.com/javase/tutorial/2d/images/examples/ImageDrawingApplet.java
 * TODO: https://docs.oracle.com/javase/tutorial/2d/images/drawimage.html
 */
public class Viewer extends Component {

    BufferedImage img;

    public void paint(Graphics g) {
        g.drawImage(img, 0, 0, null);
    }

    public Viewer() {
        try {
            img = ImageIO.read(new File("src/main/resources/strawberry.jpg"));
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }

    }

    public Dimension getPreferredSize() {
        if (img == null) {
            return new Dimension(100,100);
        } else {
            return new Dimension(img.getWidth(null), img.getHeight(null));
        }
    }

    public static void main(String[] args) {

        JFrame f = new JFrame("Load Image Sample");

        f.addWindowListener(new WindowAdapter(){
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        f.add(new Viewer());
        f.pack();
        f.setVisible(true);
    }
}

