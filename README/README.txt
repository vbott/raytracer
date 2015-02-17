/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
|                   RAYTRACER                      |
\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/

-----------------------------------------------------------------------------
SCENE ATTRIBUTES
-----------------------------------------------------------------------------

Some scene attributes can be modified by adding tags inside '<scene>' tags.

- Antialiasing
  must be a power of 2.
  calculating time increases if the number increases.
  ex: <antialiasing>2</antialiasing>


- Window size
  ex: <winx>2</winx>
      <winy>2</winy>

- Eye position
  ex: <eye>100, 0, 100</eye>

- Eye rotation
  ex: <eye_rotation>0, 0, 0</eye_rotation>

-----------------------------------------------------------------------------
HOW TO ADD AN OBJECT ?
-----------------------------------------------------------------------------

To add an object, you must add the tag '<object>' in your .xml file, between
the '<scene>' tags.
Inside, you can add other tags to specify some attributes listed below.

	ex: <scene>
		<object>
		(attributes, see below)
		</object>
	    </scene>


-----------------------------------------------------------------------------
OBJECT TYPES
-----------------------------------------------------------------------------

Object type must be specified in a '<type>' tag, inside the '<object>' tag. 
       ex:
           <object>
		<type>sphere</type>
	   </object>

 - light
 - plan
 - sphere
		Particularities :	
             	You must specify a radius.	
 - cylinder
 - cone
		Particularities :
             	You must specify a radius.

 - paraboloid
		Particularities :
             	You must specify a constant.
	     	ex: <cte>60</cte>

 - hyperboloid
		Particularities :
             	You must specify a constant.
	     	ex: <cte>1</cte>
 - disk
		Particularities :
	     	You must specify a radius.

 - parallelogram
		Particularities :
		You must specify two vectors.
		ex: <v1>1, 50, 0</v1>
	        <v2>50, 1, 0</v2>
 - torus
 - holey cube


-----------------------------------------------------------------------------
OBJECT ATTRIBUTES
-----------------------------------------------------------------------------

- type

- transparency
          <transparency>0</transparency>

- reflexion
        <reflection>0</reflection>

- img
	<img>toto.jpg</img>
- Color
  ex: <color>0x12FC9C</color>
  Put the hexadecimal value inside the tags.

- Position
  ex: <pos>800, 200, 80</pos>

- Radius
  ex: <radius>40</radius>

- Rotation
  ex: <rotation>0, 0, 10</rotation>

- Brightness
  ex: <brightness>0</brightness>

- Limits
  <limit_x>-1</limit_x>
  <limit_y>-1</limit_y>

- Refraction index
        <refract_index>0</refract_index>

- Material
