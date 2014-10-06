#include "geometricprimitive.h"
#include "binaryserializable.h"
#include "point.h"
#include "pointset.h"
#include "color.h"
#include "polygon.h"
#include "vectorpicture.h"
#include "binarymarkerdispatcher.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void dumpToFile(const BinarySerializable *obj, const char *filename)
{
    ofstream out_file;
    out_file.open(filename, ios::out | ios::binary);

    int   buf_size = obj->requiredBufferSize();
    char *bin_buf  = new char[ buf_size ];

    obj->toBinaryBuffer(bin_buf, 0, buf_size);
    out_file.write(bin_buf, buf_size);
}

bool loadFromFile(BinarySerializable *obj, const char *filename)
{
    ifstream in_file;
    in_file.open(filename, ios::in | ios::ate | ios::binary);
    if (in_file.is_open())
    {
        int    buf_size = in_file.tellg();
        char  *bin_buf  = new char[ buf_size ];

        in_file.seekg(0, ios::beg);
        in_file.read(bin_buf, buf_size);

        obj->fromBinaryBuffer(bin_buf, 0, buf_size);

        return true;
    }
    return false;
}

PointSet read()
{
    PointSet set;
    cout << "# of set: ";
    int N; cin >> N;
    set.resize(N);

    for (int i = 0; i < N; ++i)
    {
        cout << "#" << (i + 1) << ": ";
        cin >> set[i];
    }

    cout << "Points in set: " << set.size() << endl;
    for (size_t i = 0; i < set.size(); ++i)
        cout << "  Point #" << (i + 1) << ": " << set[i] << endl;

    return set;
}

void listVectorPicture(ostream &out, const VectorPicture &pic)
{
    out << "  Figures in this vector picture: " << pic.size() << endl;
    for (VectorPicture::size_type i = 0; i < pic.size(); ++i)
    {
        out << "    pic[" << i << "] = ";
        pic[i]->printInfo(out);
        out << endl;
    }
}

GeometricPrimitive* interactiveMakePrimitive()
{
    GeometricPrimitive *prim = 0;

    for (;;)
    {
        cout << "  Enter type of primitive (polygon/polyline/ellipse/curve): ";
        string prim_type;
        cin >> prim_type;

        if (prim_type == "polygon")
        {
            PointSet set;
            cout << "  Enter number of points in your polygon: ";
            int N; cin >> N;
            set.resize(N);

            for (int i = 0; i < N; ++i)
            {
                cout << "  Enter point #" << (i + 1) << ": ";
                cin >> set[i];
            }

            prim = new Polygon(set);

            cout << "  Done. \n";
            break;
        }
        else if (prim_type == "polyline")
        {
            cout << "    Sorry, not implemented yet. \n";
        }
        else if (prim_type == "ellipse")
        {
            cout << "    Sorry, not implemented yet. \n";
        }
        else if (prim_type == "curve")
        {
            cout << "    Sorry, not implemented yet. \n";
        }
        else
        {
            cout << "    Unknown type \"" << prim_type << "\". \n";
        }
    }

    return prim;
}


int main()
{
    try
    {
        BinaryMarkerDispatcher &dispatcher = *BinaryMarkerDispatcher::instance();
        dispatcher.addNewType(new Polygon());

        cout << "Input filename: ";
        string filename;
        cin >> filename;

        VectorPicture pic;
        bool loaded = loadFromFile(&pic, filename.c_str());

        if (!loaded)
        {
            cout << "Couldn't load picture from file \"" << filename << "\". ";
            cout << "Created new one." << endl;
        }

        for (;;)
        {
            cout << "Enter command (h for help):> ";
            string cmd;
            cin >> cmd;

            if (cmd == "h" || cmd == "help")
            {
                cout << "  h/help -- print help. \n"
                     << "  list   -- print list of geometric primitives \n"
                     << "            in loaded vector picture. \n"
                     << "  add    -- add new prmitive to the picture. \n"
                     << "  remove -- remove a primitive from the picture. \n"
                     << "  reload -- reload picture from file. \n"
                     << "  save   -- save changes to file. \n"
                     << "  exit   -- discard changes and exit program. \n";
            }
            else if (cmd == "list")
            {
                listVectorPicture(cout, pic);
            }
            else if (cmd == "add")
            {
                GeometricPrimitive *primitive = interactiveMakePrimitive();
                pic.push_back(primitive);
            }
            else if (cmd == "remove")
            {
                cout << "  Enter index: ";
                int idx;
                cin >> idx;

                if (idx >= 0 && idx < int(pic.size()))
                {
                    for (VectorPicture::size_type i = idx + 1; i < pic.size(); ++i)
                        pic[i - 1] = pic[i];

                    pic.pop_back();

                    cout << "  Done. \n";
                }
                else
                {
                    cout << "  Index must be in range [0, " << pic.size() << "). \n";
                }
            }
            else if (cmd == "reload")
            {
                if (loadFromFile(&pic, filename.c_str()))
                    cout << "  Loaded successfully. \n";
                else
                    cout << "  An error occured. \n";
            }
            else if (cmd == "save")
            {
                dumpToFile(&pic, filename.c_str());
                cout << "  Done. \n";
            }
            else if (cmd == "exit")
            {
                break;
            }
            else
            {
                cout << "  Unknown command \"" << cmd << "\". \n";
            }
        }
    }
    catch (const char *e)
    {
        cout << "Exception raised: " << e << endl;
    }

    return 0;
}

