## tesseract-generator

Small program that generates vertices and indices for tesseract that I used to render it as a model.
In its base form, it will end up generating edges multiple times. Four triangles are generated for one
tesseract face, even though two are needed. Comments are given in the code that point to what should be
done if fewer triangles are to be generated.