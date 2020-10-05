/*
Laboratorio 2-Grupo 3
Autores:
    Adrián Díaz Moro          UO265431
    Raúl López Calvo          UO263918
    Alejandro León Pereira    UO258774
*/

y_B = 300;
x_B = 10;
z_B = 3;

h_torn = 8;
r_torn = 2;

marge_borde_con_torn = 10;

x_caja = 10;
y_caja = 10;
z_caja = 44;

x_S = 30;
y_S = 30;
z_S = 10;

y_S_torns = 40;

d_torn_S = 40;
h_torn_S = 20;
margen_torn_S = 2;

h_herr = 50;
d_herr = 6;
margen_herr = 1;

d_torn_suj = 6;
h_torn_suj = 2;

Y_cubo = 1;
X_cubo = 50;
Z_cubo = 50;

Y_cilindro = 100;

X_torn_B = 3;
Y_torn_B = 3;

X_torn_S = 3;
Y_torn_S = 3;

X_S = 14;
Y_S = 20;
Z_S = 25;

union()
{
    difference()
    {
        rotate([ 90, 0, 90 ])
            cube(center = true, [ X_cubo, Y_cubo, Z_cubo ]);
        translate([ (X_cubo / 2 - X_torn_B), -(X_cubo / 2 - X_torn_B), 0 ])
            cylinder(center = true, h = Y_torn_B, d = X_torn_B, $fn = 300);
        translate([ -(X_cubo / 2 - X_torn_B), -(X_cubo / 2 - X_torn_B), 0 ])
            cylinder(center = true, h = Y_torn_B, d = X_torn_B, $fn = 300);
        translate([ -X_torn_B - (X_cubo / 2 - X_torn_B), X_cubo / 2, 0 ])
            cylinder(center = true, h = Y_torn_B, d = X_torn_B, $fn = 300);
        translate([ -X_torn_B + X_cubo / 2 - X_torn_B, X_cubo / 2, 0 ])
            cylinder(center = true, h = Y_torn_B, d = X_torn_B, $fn = 300);
    }
    difference()
    {
        translate([ 0, 0, Y_cilindro / 2 + Y_cubo / 2 ])
            cylinder(h = Y_cilindro, d = X_cubo - 10, center = true, $fn = 600);
        translate([ 0, 0, Y_cubo / 2 + Y_cilindro - Y_S / 2 + 1 ])
            cube([ X_S, Z_S, Y_S ], center = true);
        translate([ 0, -(Z_S / 2 + X_torn_S / 2 + margen_torn_S), Y_cubo / 2 + Y_cilindro - Y_torn_S / 2 + 1 ])
            cylinder(h = Y_torn_S, d = X_torn_S, center = true, $fn = 600);
        translate([ 0, Z_S / 2 + X_torn_S / 2 + margen_torn_S, Y_cubo / 2 + Y_cilindro - Y_torn_S / 2 + 1 ])
            cylinder(h = Y_torn_S, d = X_torn_S, center = true, $fn = 600);
    }
}

translate([ 0, y_B / 2 - marge_borde_con_torn - h_torn / 2, Y_cubo / 2 + Y_cilindro + z_B ])
{
    union()
    {
        difference()
        {
            cube([ x_B, y_B, z_B ], center = true);
            translate([ 0, -(y_B / 2) + r_torn + marge_borde_con_torn, -1 ])
            {
                cylinder(r = r_torn, h = h_torn, $fn = 400, center = true);
            }
            translate([ 0, (y_B / 2) - r_torn - marge_borde_con_torn, -1 ])
            {
                cylinder(r = r_torn, h = h_torn, $fn = 400, center = true);
            }
        }
    }
}

translate([ 0, y_B - marge_borde_con_torn - h_torn / y_caja + 2 / 2 - y_S_torns / 2 - marge_borde_con_torn, Y_cubo / 2 + z_caja + Y_cilindro / z_B + 2 * 2 ])
{
    rotate([ 0, 0, 180 ])
    {
        difference()
        {
            cube(center = true, [ x_caja, y_caja, z_caja ]);
            translate([ 0, (-y_caja / 2) - 0.01, 0 + (h_torn_suj / 2) ])
            {
                rotate([ 90, 0, 0 ])
                {
                    cylinder(d = d_torn_suj, h = h_torn_suj, $fn = 200, center = true);
                }
            }
            translate([ 0, margen_herr + (d_herr / 2) + (-y_caja / 2), 0 ])
            {
                cylinder(d = d_herr, $fn = 200, h = h_herr, center = true);
            }
            translate([ 0, -(y_S_torns / 2) + (y_caja / 2), -(z_caja / 2) - 0.01 + (z_S / 2) ])
            {
                union()
                {
                    cube(center = true, [ x_S, y_S, z_S ]);
                    translate([ 0, margen_torn_S + (d_torn_S / 2) + (y_S / 2), (h_torn_S / 2) - (z_S / 2) ])
                    {
                        cylinder(center = true, h = h_torn_S, d = d_torn_S, $fn = 200);
                    }
                    translate([ 0, -margen_torn_S - (d_torn_S / 2) - (y_S / 2), (h_torn_S / 2) - (z_S / 2) ])
                    {
                        cylinder(d = d_torn_S, $fn = 200, h = h_torn_S, center = true);
                    }
                }
            }
        }
    }
}
