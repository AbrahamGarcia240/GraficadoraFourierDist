/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servidor;

import java.awt.Color; 
import java.awt.BasicStroke; 

import org.jfree.chart.ChartPanel; 
import org.jfree.chart.JFreeChart; 
import org.jfree.data.xy.XYDataset; 
import org.jfree.data.xy.XYSeries; 
import org.jfree.ui.ApplicationFrame; 
import org.jfree.ui.RefineryUtilities; 
import org.jfree.chart.plot.XYPlot; 
import org.jfree.chart.ChartFactory; 
import org.jfree.chart.plot.PlotOrientation; 
import org.jfree.data.xy.XYSeriesCollection; 
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
/**
 *
 * @author abraham
 */
public class LineChart_AWT extends ApplicationFrame {
    final XYSeriesCollection dataset = new XYSeriesCollection( );
    public XYSeries datasets = new XYSeries( "Fourier 2" ); 
    public XYSeries datasets2 = new XYSeries( "Fourier 3" ); 
    public XYSeries datasets3 = new XYSeries( "Fourier 5" ); 
    public XYSeries datasets4 = new XYSeries( "Fourier 10" );
    public XYSeries datasets5 = new XYSeries( "Fourier 100" ); 
  
    
    public LineChart_AWT( String applicationTitle , String chartTitle ) {
     
      super(applicationTitle);
      dataset.addSeries(datasets);
      dataset.addSeries(datasets2);
      dataset.addSeries(datasets3);
      dataset.addSeries(datasets4);
      dataset.addSeries(datasets5);
      JFreeChart xylineChart = ChartFactory.createXYLineChart(chartTitle ,
         "Category" ,
         "Score" ,
          dataset,
         PlotOrientation.VERTICAL ,
         true , true , false);
        ChartPanel chartPanel = new ChartPanel( xylineChart );
        chartPanel.setPreferredSize( new java.awt.Dimension( 560 , 367 ) );
        final XYPlot plot = xylineChart.getXYPlot( );

        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer( );
        renderer.setSeriesPaint( 0 , Color.RED );
        renderer.setSeriesPaint( 1 , Color.GREEN );
        renderer.setSeriesPaint( 2 , Color.YELLOW );
        renderer.setSeriesStroke( 0 , new BasicStroke( 4.0f ) );
        renderer.setSeriesStroke( 1 , new BasicStroke( 3.0f ) );
        renderer.setSeriesStroke( 2 , new BasicStroke( 2.0f ) );
        plot.setRenderer( renderer ); 
        setContentPane( chartPanel ); 
   }
    
  

   
}
