[33mcommit 6315bddf739bd5092dc49133d40b5da180ad1752[m[33m ([m[1;36mHEAD[m[33m)[m
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Fri Dec 6 12:23:26 2019 -0500

    Revert ".."
    
    This reverts commit 26e7bd67f8e921074e31441b097a2e1d84f7d491, reversing
    changes made to af04504d6b90cead400d2a2e062c6bf6e52397ed.

[33mcommit 26e7bd67f8e921074e31441b097a2e1d84f7d491[m[33m ([m[1;32mhead-[m[33m, [m[1;32mhead[m[33m)[m
Merge: af04504 60050f6
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Thu Dec 5 14:28:47 2019 -0500

    ..

[33mcommit af04504d6b90cead400d2a2e062c6bf6e52397ed[m
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Thu Dec 5 14:12:56 2019 -0500

    j'ai changé l'algo de critére, on calcule la distance du noeud en question par rapport au noeud moyen (à partir des noeuds connectés) -- j'ai changé la condition dans la méthode "meshReduce", je l'ai remplacé par les deux conditions de vertex simple et le critére de suppression

[33mcommit 60050f6b4484dd5ffa42330ce8bb2664bd9f155e[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Thu Dec 5 10:38:27 2019 +0100

    Moved Vertex classification as a method of Vertex (vertexType())
    Added moto.stl file cause it contains different types of vertices
    Changed opengl_display code to set the vertex color according to its
    type.

[33mcommit bbb619b590086dac2cb10d4b09a683187cd77007[m
Merge: 982385e cc96df9
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Wed Dec 4 08:43:27 2019 -0500

    Merge remote-tracking branch 'refs/remotes/origin/master'

[33mcommit cc96df970d7b45abaf36f2a9ebe99ae2068fbdc8[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Wed Dec 4 14:34:58 2019 +0100

    Split the code into files.
            parse_stl --> triangle.h/cpp, vertex.h/cpp, stl_data.h/cpp
            moved every class file into "Structures" folder
            moved tools.h/cpp into "Structures" folder
            Edit the Makefile to work with this new structure

[33mcommit 982385e5062888bd48351c6592943112149bdd0b[m
Merge: a727bbf fa9355f
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Wed Dec 4 08:11:46 2019 -0500

    Merge branch 'master' of https://github.com/paulbrtrd/pol

[33mcommit fa9355f1980ef69ed0b1328db286f36515e626d3[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Wed Dec 4 10:48:21 2019 +0100

    Minor change: Modify the .gitignore file to ignore all files begining with "created_file"

[33mcommit 681b5abd116f4fd0b6ff39aa24e1f13511f1ee4a[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Tue Dec 3 12:29:26 2019 +0100

    Add retriangulation after mesh reduction (to fill the holes)

[33mcommit 4e8ace7ddd7d2d1de3efa0c8e9d65a6ff8646891[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Tue Dec 3 12:07:59 2019 +0100

    Added some methos to Vertex and Triangle
            Vertex: crossProduct, dot, invert, normalize, vectorTo
            Triangl: getv_i, getOrientation, getLastVertices

[33mcommit 748aab75690a1b10ef548f533bebe9aae629eb06[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Tue Dec 3 11:44:30 2019 +0100

    Added == operator for triangles

[33mcommit a727bbfcb734b7ce475213e347eaed76bd19b136[m
Merge: 6524bad 6b3579c
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Fri Nov 29 14:17:16 2019 -0500

    Merge remote-tracking branch 'refs/remotes/origin/master'

[33mcommit 6524bad64c3a5b54d6e7c9d1ed02624f7a92a8f9[m
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Fri Nov 29 14:15:19 2019 -0500

    ajout des algo calculant la distance du vertex au plan, pour le moment le plan est calculé pour des vertex qu'on détermine nous-même dans le code de la fonction

[33mcommit 6b3579c64cc6461038e0f8d56fd98b85091d22a0[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Thu Nov 28 21:27:25 2019 +0100

    Ajout d'un premier algo de réduction de maillage. Suppression de 1 vertex sur 5 et de ses triangles connectés, sans reconstruction.

[33mcommit 488709f916eaf52736e2f0248b246403a4623cd2[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Thu Nov 28 21:25:13 2019 +0100

    Modification mineure: suppression du endl dans la surcharge de << pour le vertex

[33mcommit 627cc692cb3fbde429c5bddc996f46a52937a755[m
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Tue Nov 26 16:24:49 2019 -0500

    vertex critirea deletion (not finished yet)

[33mcommit 304c1abbeb9f32164a1d3d0d7ba88c1bc1cbfad9[m
Merge: f50b50c 8e1966f
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Tue Nov 26 16:22:15 2019 -0500

    Merge remote-tracking branch 'refs/remotes/origin/master'

[33mcommit f50b50c51aa6aa22ef9b06972143a475f1f5e2ef[m
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Tue Nov 26 16:15:58 2019 -0500

     critirea for the deletion of the vertex (not finished yet)

[33mcommit 8e1966fdb75b930adb3a90c5c0d498411ce691aa[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Tue Nov 26 18:56:14 2019 +0100

    Modification du MakeFile: Correction

[33mcommit 4fb43c76844735abdcb4b5f0e2a85b5e493aa90b[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Sun Nov 24 14:51:28 2019 +0100

    Modification du Makefile: les .o sont construits dans le répertoire Build

[33mcommit 4b58049cdb475f0f339b9249d81ddb98cb3e20e1[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Sun Nov 24 14:39:22 2019 +0100

    Suppression du dossier recopié par erreur

[33mcommit f8ae8132e988e578dd7a8362e3f889fe59964f50[m
Author: saberkane2018 <salwa9aberkane@gmail.com>
Date:   Mon Nov 18 03:41:25 2019 -0500

    ecrire la fonction simpleVertex

[33mcommit af38fa759405d68954a008bfa2356a52d74a5037[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Sun Nov 17 10:18:24 2019 +0100

    Fixed bug with references to the vertex and normals in each triangle.
    References are no longer pointer but only integers corresponding to the index of the element in the list
    Deleted Intergalactic_Spaceship-(stl ASCII).stl cause file is not a good stl (not working with meshlab)
    Cleaned the code, added comments

[33mcommit 481a583cb973e51401b6273741d2ee13393542a4[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Fri Nov 15 22:53:24 2019 +0100

    Added normal list in Stl_data class. normals are no longer stored in the vertex list

[33mcommit 4bfff131d785e0f642a659731334cec2d34bb2ad[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Thu Nov 14 22:28:28 2019 +0100

    Added UI loop
    (openGl display crashing)

[33mcommit c960160b693ab2578f5b889046356d3ce5561042[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Thu Nov 14 21:49:48 2019 +0100

    Corrected bug (that avoided copilation)

[33mcommit e79681e8978fb8f5c040b0ec922c8a35c11371aa[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Thu Nov 14 18:38:29 2019 +0100

    Change gettriangle method to return pointer
    Deleted addVertice function (not useful cause vertices are already stored with get_or_add_vertex)

[33mcommit a5d6dec7fd249bac0cb674f308614f36e0eee1cd[m
Author: Salwa <salwa@email.com>
Date:   Fri Oct 25 08:14:03 2019 +0200

    Salwa: Added classification of vertices

[33mcommit e985f5042b7ac2c0d1181d95584a0a2918b83e74[m
Author: Salwa <salwa@email.com>
Date:   Mon Oct 21 11:22:56 2019 +0200

    Test modification

[33mcommit 40cd9e593ee7f9e45b2b5315fc9c98d90f5598da[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Mon Oct 21 10:04:26 2019 +0200

    Added camera control on openGL (not fonctioning well)

[33mcommit e5a82b8034560b5243bd7cf41aedf834b6be76ce[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Sun Oct 20 22:13:26 2019 +0200

    Added openGL support: Display of a mesh from a Stl_data object
    Added rabbit.stl as a more complex example of binary stl
    Added Makefile in GIT
    Start ignoring *.o files and myApp (with .gitignore)

[33mcommit b4236fb2a1f8f557a4fbd68df9dbe8c5922f1fb6[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Fri Oct 18 11:04:01 2019 +0200

    Deleted unuseful files

[33mcommit 46e21735e0d1200347687d8f485ad318524a4100[m
Author: Paul <paul.bertrand@eleves.ec-nantes.fr>
Date:   Fri Oct 18 10:55:15 2019 +0200

    Added first version of stl reader / writer

[33mcommit 1960ff0d6e045f61f874b6945bdb34adff2724bd[m
Author: paulbrtrd <56717458+paulbrtrd@users.noreply.github.com>
Date:   Fri Oct 18 10:18:12 2019 +0200

    Initial commit
