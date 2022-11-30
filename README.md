# How to use
NumPy with SVE support will be installed by following comand.
```
python setup.py install
```
The basic usage is the same as the original NumPy.
Please refer to the following page.
- https://github.com/numpy/numpy
  
To change the vector length of SVE to 512 bits, change as follows.

```
--- a/numpy/distutils/ccompiler_opt.py
+++ b/numpy/distutils/ccompiler_opt.py
@@ -538,7 +538,7 @@ class attribute `conf_features`, also its override
             ),
             SVE = dict(
                 implies="ASIMDHP",
-                flags="-march=armv8.2-a+sve -msve-vector-bits=256",
+                flags="-march=armv8.2-a+sve -msve-vector-bits=512",
                 autovec=True
             ),
         )
```