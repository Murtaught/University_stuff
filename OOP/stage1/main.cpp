#include "geometricprimitive.h"
#include "binaryserializable.h"
#include "point.h"
#include "color.h"
#include "polygon.h"
#include "ellipse.h"
#include "vectorpicture.h"
#include "binarymarkerdispatcher.h"
#include "bytearray.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void dumpToFile(const BinarySerializable *obj, const char *filename)
{
    ofstream out_file;
    out_file.open(filename, ios::out | ios::binary);

    ByteArray ba = obj->toByteArray();
    out_file.write(ba.data(), ba.size());
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

        ByteArray ba(bin_buf, buf_size);
        ByteArrayReader bar(&ba);
        obj->fromByteArray(bar);

        return true;
    }
    return false;
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
            cout << "  Enter number of points in your polygon: ";
            int N; cin >> N;
            std::vector<Point> set(N);

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
    // TODO написать класс BinaryBuffer
    // ужать Color в 4 байта вместо 16
    // пройтись по коду и заменить сишные касты на плюсовые static_cast и dynamic_cast
    // убрать наследование VectorPicture от вектора указателей на примитивы
    // возможно, подключить сюда boost::shared_ptr
    // сделать нормальную систему эксепшонов
    // создать отдельные проекты для редактора и библиотеки, связать их системой сборки

    /*VectorPicture pic;

    {
        Point a(10, 0), b(0, 42), c(-42, 69);
        std::vector<Point> vp;
        vp.push_back(a);
        vp.push_back(b);
        vp.push_back(c);

        Polygon *poly = new Polygon(vp);
        pic.push_back(poly);
    }

    {
        Ellipse *elly = new Ellipse(Point(7, 13), 4, 2);
        elly->rotate(45.0, elly->center());

        pic.push_back(elly);
    }

    dumpToFile(&pic, "pic.bin");*/



    /*{
        BinaryPrinter izer;

        int some_int = 0x0ABACABA;
        izer.add(some_int);
        izer.add(some_int);

        izer.add('M');
        izer.add('M');
        izer.add('M');

        float some_float = 1488;
        double some_double = 3.1415;
        izer.add(some_float);
        izer.add(some_double);

        izer.add('M');
        izer.add('M');
        izer.add('M');

        Point some_point(42, 69);
        izer.add(some_point);

        ofstream out_file;
        out_file.open("IZER.dump", ios::out | ios::binary);
        out_file.write(izer.get(), izer.getSize());
    }*/

    /*{
        ifstream in_file;
        in_file.open("IZER.dump", ios::in | ios::ate | ios::binary);
        int    buf_size = in_file.tellg();
        char  *bin_buf  = new char[ buf_size ];
        in_file.seekg(0, ios::beg);
        in_file.read(bin_buf, buf_size);

        BinaryBufferScanner scanner(bin_buf, buf_size);

        int some_int1, some_int2;
        scanner.scan(some_int1);
        scanner.scan(some_int2);
        printf("%08X %08X \n", some_int1, some_int2);

        char char1 = scanner.scanNext<char>();
        char char2 = scanner.scanNext<char>();
        char char3 = scanner.scanNext<char>();
        cout << char1 << char2 << char3 << endl;

        float some_float = scanner.scanNext<float>();
        double some_double = scanner.scanNext<double>();
        cout << some_float << endl << some_double << endl;

        char1 = scanner.scanNext<char>();
        char2 = scanner.scanNext<char>();
        char3 = scanner.scanNext<char>();
        cout << char1 << char2 << char3 << endl;

        Point some_point = scanner.scanNext<Point>();
        cout << some_point << endl;
    }*/

    try
    {
        BinaryMarkerDispatcher &dispatcher = *BinaryMarkerDispatcher::instance();
        dispatcher.addNewType(new Polygon);
        dispatcher.addNewType(new Ellipse);

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
            else if (cmd == "rotate")
            {
                cout << pic[0]->massCenter() << endl;
                pic[0]->rotate(45);
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

